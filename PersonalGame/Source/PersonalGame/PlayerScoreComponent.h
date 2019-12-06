// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerScoreComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONALGAME_API UPlayerScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	int32 GetTotalShots() const;
	UFUNCTION(BlueprintCallable)
	int32 GetNumberHit() const;
	UFUNCTION(BlueprintCallable)
	int32 GetNumberKilled() const;
	UFUNCTION(BlueprintCallable)
	void IncrementTotalShots();
	UFUNCTION(BlueprintCallable)
	void IncrementNumKilled();
	UFUNCTION(BlueprintCallable)
	void IncrementNumHit();
	UFUNCTION(BlueprintCallable)
		float GetTimePlayed() const;
	
	UFUNCTION(BlueprintCallable)
	float GetScoreDamageMultiplier() const;

	void ResetScoreComponent();
	
	void StopTime();

	void ResetHitStreak();
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int32 TotalShots;
	int32 NumberHit;
	int32 NumberKilled;
	//Streak of hitting a shootable without being hit by 
	int32 HitStreak;
	float StartTime;
	float EndTime;

	UPROPERTY(EditAnywhere)
	int32 StreakRequiredToFirstDamageMultiplier = 2;

	UPROPERTY(EditAnywhere)
	int32 StreakRequiredToSecondDamageMultiplier = 3;

	UPROPERTY(EditAnywhere)
	float BaseDamageMultiplierValue = 1.f;

	UPROPERTY(EditAnywhere)
	float FirstDamageMultiplierValue = 2.f;

	UPROPERTY(EditAnywhere)
	float SecondDamageMultiplierValue = 3.f;
		
};
