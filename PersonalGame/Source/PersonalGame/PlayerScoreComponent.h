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
	// Sets default values for this component's properties
	UPlayerScoreComponent();
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
	
	void ResetScoreComponent();
	
	void StopTime();
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int32 TotalShots;
	int32 NumberHit;
	int32 NumberKilled;
	float StartTime;
	float EndTime;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
