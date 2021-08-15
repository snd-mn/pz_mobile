// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TilePz.h"
#include "GameFramework/Actor.h"
#include "NodeRegistry.generated.h"

UCLASS()
class PZ_MOBILE_API UNodeRegistry : public UActorComponent
{
	GENERATED_BODY()

public:
//	// Sets default values for this actor's properties
//	ANodeRegistry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TMap<int64,UTilePz*> Tiles = TMap<int64,UTilePz*>();

	TMap<int64,UNodePz*> Nodes = TMap<int64,UNodePz*>();
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UpdateTiles(UPARAM(ref) TArray<UTilePz*>& tiles);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UTilePz* GetTileForId(int64 id);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UTilePz* GetTileForXY(int64 x, int64 y);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UNodePz* GetNodeForId(int64 id);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<UNodePz*> GetNodesInRange(float lat, float lon, float radius);
	
};
