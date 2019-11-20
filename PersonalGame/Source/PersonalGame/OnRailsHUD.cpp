// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailsHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/GameViewportClient.h"
#include "UObject/ConstructorHelpers.h"

AOnRailsHUD::AOnRailsHUD()
{
}

void AOnRailsHUD::DrawHUD()
{
	Super::DrawHUD();
	
	CalculateCrossHairPos();
	FCanvasTileItem TileItem{ CrossHairPos, CrossHairTexture->Resource, FLinearColor::White };
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AOnRailsHUD::CalculateCrossHairPos()
{
	
	float ScreenX, ScreenY;
	UWorld const * World = GetWorld();
	if (World != nullptr)
	{
		APlayerController * PC = World->GetFirstPlayerController();
		if (PC != nullptr)
		{
			if (PC->GetMousePosition(ScreenX, ScreenY))
			{
				float width, height;
				World->GetGameViewport()->GetPixelSizeOfScreen(width, height, Canvas, 0);
				ScreenX /= width;
				ScreenY /= height;
				CrossHairPos = { Canvas->ClipX * ScreenX, Canvas->ClipY  * ScreenY };
			}

		}
	}
}
