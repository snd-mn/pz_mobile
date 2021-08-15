// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodePz.generated.h"

UCLASS(BlueprintType, Category="PZ")
class PZ_MOBILE_API UNodePz : public UObject
{
	public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float lat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float lon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 nextAvailability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 nodeType;
	
};
