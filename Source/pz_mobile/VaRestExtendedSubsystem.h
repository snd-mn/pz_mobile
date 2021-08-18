// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VaRestSubsystem.h"
#include "UObject/Object.h"
#include "VaRestExtendedSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PZ_MOBILE_API UVaRestExtendedSubsystem : public UVaRestSubsystem
{
	GENERATED_BODY()

public:
	UVaRestExtendedSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CallExtended(const FString& URL, EVaRestRequestVerb Verb, EVaRestRequestContentType ContentType, UVaRestJsonObject* VaRestJson, const FVaRestCallDelegate& Callback, TMap<FString, FString>& Headers);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCallCompleteExtended(UVaRestRequestJSON* Request);

	
};
