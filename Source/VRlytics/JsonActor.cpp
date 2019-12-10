// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonActor.h"
#include "DOM/JsonObject.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"



// Sets default values
AJsonActor::AJsonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

// Called when the game starts or when spawned
void AJsonActor::BeginPlay()
{

	Super::BeginPlay();
	
	const FString JsonFilePath = FPaths::ProjectContentDir() + "/data/iris.json";
	FString JsonString; //Json converted to FString

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	//Displaying the json in a string format inside the output log
	GLog->Log("Json String:");
	GLog->Log(JsonString);

	//Create a json object to store the information from the json string
	//The json reader is used to deserialize the json object later on
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		//The person "object" that is retrieved from the given json file
		IrisArray = JsonObject->GetArrayField("data");
		for (auto row : IrisArray)
		{
			TSharedPtr<FJsonObject> IrisObject = row->AsObject();
			//Getting various properties
			GLog->Log("sepalLength:" + FString::SanitizeFloat(IrisObject->GetNumberField("sepalLength")));
			GLog->Log("sepalWidth:" + FString::SanitizeFloat(IrisObject->GetNumberField("sepalWidth")));
			GLog->Log("petalLength" + FString::SanitizeFloat(IrisObject->GetNumberField("petalLength")));
			GLog->Log("petalWidth:" + FString::SanitizeFloat(IrisObject->GetNumberField("petalWidth")));
			GLog->Log("species:" + IrisObject->GetStringField("species"));
		}
	}
	else
	{
		GLog->Log("couldn't deserialize");
	}
}

// Called every frame
void AJsonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

