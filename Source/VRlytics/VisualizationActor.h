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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* meshActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dataPoints")
		TArray<class UStaticMeshComponent*> dataPoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool isDataValid = false;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialRed;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialBlue;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* materialGreen;
	class TArray<TSharedPtr<class FJsonValue>> IrisArray;

	bool readJsonToArray();
	UFUNCTION(CallInEditor)
		void switchMarkCode();
	UFUNCTION(CallInEditor)
		void drawData();
};
