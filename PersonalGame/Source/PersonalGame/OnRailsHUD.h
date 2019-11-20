// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OnRailsHUD.generated.h"

/**
 * 
 */
UCLASS()
class PERSONALGAME_API AOnRailsHUD : public AHUD
{
	GENERATED_BODY()
public:
		AOnRailsHUD();
		virtual void DrawHUD() override;
protected:
	UPROPERTY(EditAnywhere)
	class  UTexture2D * CrossHairTexture;

	FVector2D CrossHairPos;

	void CalculateCrossHairPos();


};
