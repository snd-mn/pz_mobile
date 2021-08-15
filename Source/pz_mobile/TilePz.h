// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodePz.h"
#include "TilePz.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType, Category="PZ")
struct PZ_MOBILE_API FTilePz
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 x;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 y;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNodePz> nodes;
};
