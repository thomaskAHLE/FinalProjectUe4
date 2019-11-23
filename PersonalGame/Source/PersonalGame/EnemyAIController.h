// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PERSONALGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TravelToPoint(class ATargetPoint * NextPointToTravelTo);

	UFUNCTION(BlueprintCallable)
	void TravelToActor(class AActor * ActorToTravelTo);

protected:
	UPROPERTY(EditAnywhere)
	class ATargetPoint * PointToTravelTo;

	UPROPERTY(EditAnywhere)
	class AActor * ActorToTravelTo;

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
};
