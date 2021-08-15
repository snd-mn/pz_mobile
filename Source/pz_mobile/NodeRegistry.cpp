// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeRegistry.h"


// Sets default values
//UNodeRegistry::UNodeRegistry()
//{
//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//}

// Called when the game starts or when spawned
void UNodeRegistry::BeginPlay()
{
	Super::BeginPlay();
}

void UNodeRegistry::UpdateTiles_Implementation(UPARAM(ref) TArray<UTilePz*>& tiles)
{
	for (int i = 0; i < tiles.Num(); i++)
	{
		UTilePz* newTile = tiles[i];
		TArray<UNodePz*> newNodes = newTile->nodes;

		UTilePz* oldTile = nullptr;
		if (Tiles.Contains(newTile->id))
		{
			oldTile = *Tiles.Find(newTile->id);
		}

		if (oldTile)
		{
			//update values and remove the given tile
			TArray<UNodePz*>& oldNodes = oldTile->nodes;

			TArray<int64> updatedNodeIds = TArray<int64>();
			for (int j = 0; j < oldNodes.Num(); j++)
			{
				UNodePz* oldNode = oldNodes[j];

				bool found = false;
				for (int k = 0; k < oldNodes.Num(); k++)
				{
					UNodePz* newNode = newNodes[k];
					if (oldNode->id == newNode->id)
					{
						//update node
						updatedNodeIds.Add(oldNode->id);
						oldNode->lat = newNode->lat;
						oldNode->lon = newNode->lon;
						found = true;
						break;
					}
					if (found)
					{
						//TODO concurrent exeption?
						oldNodes.Remove(oldNode);
					}
				}
			}
			if (updatedNodeIds.Num() != newNodes.Num())
			{
				//add the new ones
				for (int l = 0; l < oldNodes.Num(); l++)
				{
					UNodePz* newNode = newNodes[l];
					bool found = false;

					for (int m = 0; m < oldNodes.Num(); m++)
					{
						int64 updatedNodeId = updatedNodeIds[m];
						found = updatedNodeId == newNode->id;
						if (found)
						{
							break;
						}
					}
					if (!found)
					{
						oldTile->nodes.Add(newNode);
						Nodes.Add(newNode->id, newNode);
					}
				}
			}
		}
		else
		{
			//insert
			Tiles.Add(tiles[i]->id, newTile);
			for (int j = 0; j < newTile->nodes.Num(); j++)
			{
				UNodePz* newNode = newTile->nodes[j];
				UE_LOG(LogTemp, Warning, TEXT("ich fress gleich n besen %i"), newNode->id)
				Nodes.Add(newNode->id, newNode);
			}
		}
	}
}

TArray<UNodePz*> UNodeRegistry::GetNodesInRange_Implementation(float lat, float lon, float radius)
{
	return TArray<UNodePz*>();
}

UNodePz* UNodeRegistry::GetNodeForId_Implementation(int64 id)
{
	return nullptr;
}

UTilePz* UNodeRegistry::GetTileForXY_Implementation(int64 x, int64 y)
{
	return nullptr;
}

UTilePz* UNodeRegistry::GetTileForId_Implementation(int64 id)
{
	return nullptr;
}

void UNodeRegistry::TickComponent(float DeltaTime, ELevelTick TickType,
                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
