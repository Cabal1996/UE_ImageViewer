// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"
#include "ImageViewerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class IMAGEVIEWER_API UImageViewerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "DIR", meta = (Keywords = "image png jpg jpeg bmp"))
	static UTexture2D* GetTextureByPath(const FString& FullFilePath, const FVector2D& ScreenSize, bool& IsValid, int32& Width, int32& Height);
	

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	UTexture2D* Texture;

	UFUNCTION(BlueprintPure, Category = "DIR")
	static bool GetDirs(TArray<FString>& FileNames, FString RootFolderFullPath);

	UFUNCTION(BlueprintPure, Category = "DIR")
	static bool GetFiles(TArray<FString>& FolderNames, FString RootFolderFullPath, FString Ext);
	
};
