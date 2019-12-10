// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualizationActor.h"
#include "JsonActor.h"
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

	/*jsonChildActor = NewObject<UChildActorComponent>(this);
	jsonChildActor->bEditableWhenInherited = true;
	jsonChildActor->RegisterComponent();
	jsonChildActor->SetChildActorClass(AJsonActor::StaticClass());
	jsonChildActor->CreateChildActor();*/

	//jActor = CreateDefaultSubobject<AJsonActor>(TEXT("JsonActor"));
	

	sphere = NewObject<UStaticMeshComponent>(this);
	sphere->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	sphere->SetStaticMesh(mesh);
	sphere->RegisterComponent();
	
	if (jActor) {
		TSharedPtr<FJsonObject> IrisObject = jActor->IrisArray[0]->AsObject();
		sphere->SetRelativeLocation(FVector(IrisObject->GetNumberField("sepalLength"), IrisObject->GetNumberField("sepalWidth"), IrisObject->GetNumberField("petalLength")));
	}
	else sphere->SetRelativeLocation(FVector(100,100,100));
	
}

// Called every frame
void AVisualizationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

