// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodePz.h"
#include "TilePz.generated.h"

UCLASS(BlueprintType, Category="PZ")
class PZ_MOBILE_API UTilePz : public UObject
{
	public:
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 x;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 y;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UNodePz*> nodes = TArray<UNodePz*>();
};
