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

	if (readJsonToArray())
	{
		//The person "object" that is retrieved from the given json file
		for (auto row : IrisArray) {
			TSharedPtr<FJsonObject> IrisObject = row->AsObject();
			FTransform transformation(FVector(IrisObject->GetNumberField("sepalLength"), IrisObject->GetNumberField("sepalWidth"), IrisObject->GetNumberField("petalLength")));
			transformation.ScaleTranslation(50);
			transformation.SetScale3D(FVector(0.02, 0.02, 0.02));

			UStaticMeshComponent* newSphere = NewObject<UStaticMeshComponent>(this);
			newSphere->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			newSphere->SetStaticMesh(mesh);
			newSphere->SetCollisionProfileName(TEXT("NoCollision"));
			newSphere->SetWorldTransform(transformation);
			newSphere->RegisterComponent();
			if (IrisObject->GetStringField("species") == "setosa") {
				newSphere->SetMaterial(0, materialBlue);
			}
			if (IrisObject->GetStringField("species") == "versicolor") {
				newSphere->SetMaterial(0, materialRed);
			}
			if (IrisObject->GetStringField("species") == "virginica") {
				newSphere->SetMaterial(0, materialGreen);
			}

			spheres.Add(newSphere);
		}
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

