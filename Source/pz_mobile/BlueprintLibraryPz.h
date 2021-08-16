// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlueprintLibraryPz.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName="StringLibraryPz"))
class PZ_MOBILE_API UBlueprintLibraryPz : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	/** Converts an int64 value to a string */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "ToString (int64)", CompactNodeTitle = "->", BlueprintAutocast), Category="Utilities|String")
	static FString Conv_Int64ToString(int64 int64)
	{
		return FString::Printf(TEXT("%lld"), int64);
	};
};
