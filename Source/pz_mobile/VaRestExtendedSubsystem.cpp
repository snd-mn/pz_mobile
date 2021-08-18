// Fill out your copyright notice in the Description page of Project Settings.


#include "VaRestExtendedSubsystem.h"

UVaRestExtendedSubsystem::UVaRestExtendedSubsystem()
	: UVaRestSubsystem()
{
}

void UVaRestExtendedSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UVaRestExtendedSubsystem::Deinitialize()
{
	// Do nothing for now
	Super::Deinitialize();
}


void UVaRestExtendedSubsystem::CallExtended_Implementation(const FString& URL, EVaRestRequestVerb Verb, EVaRestRequestContentType ContentType, UVaRestJsonObject* VaRestJson, const FVaRestCallDelegate& Callback, TMap<FString, FString>& Headers)
{
	// Check we have valid data json
	if (VaRestJson == nullptr)
	{
		VaRestJson = ConstructVaRestJsonObject();
	}
	
	UVaRestRequestJSON* Request = ConstructVaRestRequest();
	
	Request->SetVerb(Verb);
	Request->SetContentType(ContentType);
	Request->SetRequestObject(VaRestJson);
	
	for (const TPair<FString, FString>& pair : Headers)
	{
		Request->SetHeader(pair.Key, pair.Value);
	}
		
	FVaRestCallResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	
	Response.CompleteDelegateHandle = Request->OnStaticRequestComplete.AddUObject(this, &UVaRestExtendedSubsystem::OnCallComplete);
	Response.FailDelegateHandle = Request->OnStaticRequestFail.AddUObject(this, &UVaRestExtendedSubsystem::OnCallComplete);
	
	RequestMap.Add(Request, Response);
	
	Request->ResetResponseData();
	Request->ProcessURL(URL);
}

void UVaRestExtendedSubsystem::OnCallCompleteExtended_Implementation(UVaRestRequestJSON* Request)
{
	if (!RequestMap.Contains(Request))
	{
		return;
	}
	
	const auto Response = RequestMap.Find(Request);
	Request->OnStaticRequestComplete.Remove(Response->CompleteDelegateHandle);
	Request->OnStaticRequestFail.Remove(Response->FailDelegateHandle);
	
	Response->Callback.ExecuteIfBound(Request);
	Response->Request = nullptr;
	RequestMap.Remove(Request);
}

