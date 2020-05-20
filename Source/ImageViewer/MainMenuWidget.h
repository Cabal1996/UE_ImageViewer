// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UImage;
class UButton;

/**
 * 
 */
UCLASS()
class IMAGEVIEWER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	

protected:
	//Protected Overrides
	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_96;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ShowButton;

private:

};
