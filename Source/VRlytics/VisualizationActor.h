// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisualizationActor.generated.h"

UCLASS()
class VRLYTICS_API AVisualizationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisualizationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialRed;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialBlue;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialGreen;
	class TArray<class UStaticMeshComponent*> spheres;
	class TArray<TSharedPtr<class FJsonValue>> IrisArray;

	bool readJsonToArray();
};
