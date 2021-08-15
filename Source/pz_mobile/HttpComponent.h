// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HttpModule.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IHttpRequest.h"

#include "HttpComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PZ_MOBILE_API UHttpComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UHttpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FHttpModule* Http;
	// int LogHttp;

	UFUNCTION(BlueprintCallable)
	void MyHttpCall();
};
