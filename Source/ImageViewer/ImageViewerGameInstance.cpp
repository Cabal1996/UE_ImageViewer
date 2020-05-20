// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageViewerGameInstance.h"
#include "HAL/FileManager.h"
#include "Modules/ModuleManager.h"
#include "IImageWrapperModule.h"
#include "Misc/FileHelper.h"
#include "Templates/SharedPointer.h"



UTexture2D* UImageViewerGameInstance::GetTextureByPath(const FString& FullFilePath, const FVector2D& ScreenSize, bool& IsValid, int32& Width, int32& Height)
{
	IsValid = false;
	UTexture2D* LoadedT2D = NULL;
	
	//Checking image format
	EImageFormat ImageFormat = EImageFormat::Invalid;
	if (FullFilePath.Contains("."))
	{
		
		const TArray<TCHAR>& PathAsArray = FullFilePath.GetCharArray();
		FString FormatAsString;
		for (int i = PathAsArray.Num() - 1; i >= 0; i--)
		{
			if (PathAsArray[i] == '.') break;
			FormatAsString.InsertAt(0, PathAsArray[i]);
		}

		if (FormatAsString.Contains("jpg") || FormatAsString.Contains("jpeg")) ImageFormat = EImageFormat::JPEG;
		else if (FormatAsString.Contains("png")) ImageFormat = EImageFormat::PNG;
		else if (FormatAsString.Contains("bmp")) ImageFormat = EImageFormat::BMP;
		else if (FormatAsString.Contains("ico")) ImageFormat = EImageFormat::ICO;
		else if (FormatAsString.Contains("icns")) ImageFormat = EImageFormat::ICNS;
		

	}
	if (ImageFormat == EImageFormat::Invalid) return NULL;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	//Load From File
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FullFilePath)) return NULL;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Create T2D!
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			//Valid?
			if (!LoadedT2D) return NULL;
			
			//Out!
			//Size calc
			if (ImageWrapper->GetWidth() >= ImageWrapper->GetHeight())
			{
				Height = (ScreenSize.X * ImageWrapper->GetHeight()) / ImageWrapper->GetWidth();
				Width = ScreenSize.X;

			}
			else
			{
				Width = (ScreenSize.Y * ImageWrapper->GetWidth()) / ImageWrapper->GetHeight();
				Height = ScreenSize.Y;
			}

			//Copy!
			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			LoadedT2D->UpdateResource();
		}
	}

	

	// Success!
	IsValid = true;
	return LoadedT2D;
}

bool UImageViewerGameInstance::GetDirs(TArray<FString>& FolderNames, FString RootFolderFullPath)
{

	if (RootFolderFullPath.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(RootFolderFullPath);

	IFileManager& FileManager = IFileManager::Get();

	FString FinalPath = RootFolderFullPath + "/*.*";

	FileManager.FindFiles(FolderNames, *FinalPath, false, true);

	return true;
}


bool UImageViewerGameInstance::GetFiles(TArray<FString>& FileNames, FString RootFolderFullPath, FString Ext)
{
	if (RootFolderFullPath.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(RootFolderFullPath);

	IFileManager& FileManager = IFileManager::Get();

	if (!Ext.Contains(TEXT("*")))
	{
		if (Ext == "")
		{
			Ext = "*.*";
		}
		else
		{
			Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
		}
	}

	FString FinalPath = RootFolderFullPath + "/" + Ext;

	FileManager.FindFiles(FileNames, *FinalPath, true, false);

	return true;
}