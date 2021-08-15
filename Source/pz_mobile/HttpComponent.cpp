// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpComponent.h"

#include <string>

#include "Interfaces/IHttpResponse.h"


// Sets default values for this component's properties
UHttpComponent::UHttpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Http = &FHttpModule::Get();
	// ...
}


// Called when the game starts
void UHttpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHttpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
static const wchar_t* blub = TEXT("{	\"gps\":{\"lat\":\"51.50889155160364\",	\"lon\":\"7.464675695954779\"}}");;
static FString* blbbb = new FString(blub);


/*Http call*/
void UHttpComponent::MyHttpCall()
{
	// TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UHttpComponent::OnResponseReceived);
	//This is the url on which to process the request
	


	
	
	// Request->SetURL(TEXT("http://127.0.0.1:12224/tiles"));
	// Request->SetVerb(TEXT("GET"));
	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	// Request->SetHeader(TEXT("Authorization"), TEXT("Basic dXNlckBsb2NhbC10cmluaXR5Lm9yZzpzdXBlcnNhZmVwYXNzd29yZA=="));
	//
	// FString asdf = TEXT("{	\"gps\":{\"lat\":\"51.50889155160364\",	\"lon\":\"7.464675695954779\"}}");
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *asdf)
	// Request->SetContentAsString(*blbbb);


	// Request->SetURL(TEXT("http://127.0.0.1:12224/pingbody"));
	// Request->SetVerb(TEXT("GET"));
	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	// Request->SetHeader(TEXT("Authorization"), TEXT("Basic dXNlckBsb2NhbC10cmluaXR5Lm9yZzpzdXBlcnNhZmVwYXNzd29yZA=="));
	// Request->SetContentAsString("dummy text");

	
	// UE_LOG(LogTemp, Warning, TEXT("%s"), Request->GetContent())
	// BytesToString(Request->GetContent());
	// FString fromBlob = FString::FromBlob(Request->GetContent().GetData(), Request->GetContentLength())
	// UE_LOG(LogTemp, Warning, TEXT("%s"), fromBlob)

	// char ansiiData[1024]; //A temp buffer for the data
 //
	// memcpy(ansiiData, Request->GetContent().GetData(), Request->GetContentLength()); //Assumes bytesRead is always smaller than 1024 bytes
 //
	// ansiiData[Request->GetContentLength()] = 0; //Add null terminator
 //
	// FString debugData = ANSI_TO_TCHAR(ansiiData); //Convert to FString
	// UE_LOG(LogTemp, Warning, TEXT("%s"), debugData)

	
	// FString ret;
	// for (uint8 Content : Request->GetContent())
	// {
	// 	char c = Content;
	// 	std::string str = c ;
	// 	FString append = FString();
	// 	ret.Append(append);
	// }
	
	// UE_LOG(LogTemp, Warning, TEXT("%s"), ret)
	
	// Request->SetURL(TEXT("http://127.0.0.1:12224/ping"));
	// Request->SetVerb(TEXT("GET"));
	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	// Request->SetHeader(TEXT("Authorization"), TEXT("Basic dXNlckBsb2NhbC10cmluaXR5Lm9yZzpzdXBlcnNhZmVwYXNzd29yZA=="));

	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void UHttpComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// //Create a pointer to hold the json serialized data
	// TSharedPtr<FJsonObject> JsonObject;
	//
	// //Create a reader pointer to read the json data
	// TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//
	// //Deserialize the json data given Reader and the actual object to deserialize
	// if (FJsonSerializer::Deserialize(Reader, JsonObject))
	// {
	// 	//Get the value of the json object by field name
	// 	
	// 	//Output it to the engine
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString())

	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Response->GetContentAsString());
	// }
}
