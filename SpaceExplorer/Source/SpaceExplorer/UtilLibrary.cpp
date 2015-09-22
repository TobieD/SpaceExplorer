// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceExplorer.h"
#include "UtilLibrary.h"


void UUtilLibrary::SampleTexture(UTexture2D* tex, TArray<FLinearColor> &vecArr)
{
	vecArr.Empty();
	if (!tex) return;

	//Access mipmap 0 (original size) of the texture (address)
	FTexture2DMipMap* texMipMap = &tex->PlatformData->Mips[0];

	if (!texMipMap) return;

	//Access raw image data from mip map
	FByteBulkData* rawImgData = &texMipMap->BulkData;

	//texture is used in rendering thread so we need to lock it first this sends back the data
	//We want to access the color so cast it an array of FColor
	FColor* formatedRawData = static_cast<FColor*>(rawImgData->Lock(LOCK_READ_ONLY));

	//get texture size
	int texWidth = tex->GetSizeX(), texHeight = tex->GetSizeY();

	//Create linear Color Array
	for (int x = 0; x < texWidth; ++x)
	{

		for (int y = 0; y < texHeight; ++y)
		{
			FColor c = formatedRawData[x * texWidth + y];
			vecArr.Add(FLinearColor(c));
		}
	}


	//unlock it again
	rawImgData->Unlock();
}

AActor* UUtilLibrary::SpawnActor(UObject* worldObject, UClass* actorClass, const FTransform relativeTransform, const FString name)
{
	if (!worldObject || !actorClass)
		return nullptr;

	//set spawn to allow in construction script
	FActorSpawnParameters spawnParam;
	spawnParam.bAllowDuringConstructionScript = true;
	AActor* p = worldObject->GetWorld()->SpawnActor<AActor>(actorClass, spawnParam);

	p->SetActorTransform(relativeTransform);

	return p;
}

bool UUtilLibrary::RemoveActor(UObject* inputObject, AActor* actor)
{
	bool bSucceed = false;
	if (!actor) return bSucceed;

	//inputObject->GetWorld()->RemoveActor(actor,true);
	actor->K2_DestroyActor();

	actor = NULL;

	//GC
	inputObject->GetWorld()->ForceGarbageCollection(true);

	bSucceed = true;
	return bSucceed;
}

