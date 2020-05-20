// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Image.h"
#include "ImageViewerGameInstance.h"

bool UMainMenuWidget::Initialize()
{
	
	bool Success = Super::Initialize();
	if (!Success) return false;
	/*
	UImageViewerGameInstance* GI = Cast<UImageViewerGameInstance>(GetGameInstance());
	UTexture2D* Textute = GI ? GI->GetTextureByPath() : nullptr;
	if (!Textute)
	{
		UE_LOG(LogTemp, Warning, TEXT("Image invalid"))
		return Success;
	}

	Image_96->SetBrushFromTexture(Textute);
	*/

	return Success;

}

