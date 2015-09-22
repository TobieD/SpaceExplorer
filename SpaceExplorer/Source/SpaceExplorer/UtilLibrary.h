// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPACEEXPLORER_API UUtilLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
	
public:
	UFUNCTION(BlueprintCallable, Category = "C++ Utilities")
	static void SampleTexture(UTexture2D* tex, TArray<FLinearColor> &vecArr);

	UFUNCTION(BlueprintCallable, Category = "C++ Utilities")
	static AActor* SpawnActor(UObject* worldObject, UClass* actorClass, const FTransform relativeTransform, const FString name);

	UFUNCTION(BlueprintCallable, Category = "C++ Utilities")
	static bool RemoveActor(UObject* inputObject, AActor* actorClass);
	
};
