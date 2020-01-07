// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualizationActor.h"
#include "Components/StaticMeshComponent.h"
#include "DOM/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values
AVisualizationActor::AVisualizationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVisualizationActor::BeginPlay()
{
	Super::BeginPlay();
	isDataValid = readJsonToArray();
	if (isDataValid)
	{
		drawData();
	}
}

// Called every frame
void AVisualizationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AVisualizationActor::readJsonToArray()
{
	const FString JsonFilePath = FPaths::ProjectContentDir() + "/data/iris.json";
	FString JsonString; //Json converted to FString

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	if(!JsonObject.IsValid())
		return false;
	IrisArray = JsonObject->GetArrayField("data");
	return true;
}

void AVisualizationActor::switchMarkCode() {

	for (UStaticMeshComponent* sm : dataPoints)
		sm->SetStaticMesh(meshActive);
}

void AVisualizationActor::drawData() {
	if (isDataValid) {
		for (auto row : IrisArray) {
			TSharedPtr<FJsonObject> IrisObject = row->AsObject();
			FTransform transformation(FVector(IrisObject->GetNumberField("sepalLength"), IrisObject->GetNumberField("sepalWidth"), IrisObject->GetNumberField("petalLength")));
			transformation.ScaleTranslation(50);
			transformation.SetScale3D(FVector(0.02, 0.02, 0.02));

			UStaticMeshComponent* newDataPoint = NewObject<UStaticMeshComponent>(this);
			newDataPoint->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			newDataPoint->SetStaticMesh(meshActive);
			newDataPoint->SetCollisionProfileName(TEXT("NoCollision"));
			newDataPoint->SetWorldTransform(transformation);
			newDataPoint->RegisterComponent();
			if (IrisObject->GetStringField("species") == "setosa") {
				newDataPoint->SetMaterial(0, materialBlue);
			}
			if (IrisObject->GetStringField("species") == "versicolor") {
				newDataPoint->SetMaterial(0, materialRed);
			}
			if (IrisObject->GetStringField("species") == "virginica") {
				newDataPoint->SetMaterial(0, materialGreen);
			}

			dataPoints.Add(newDataPoint);
		}
	}
}