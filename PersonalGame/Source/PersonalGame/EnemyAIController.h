// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveCompletedSuccessSignature);

UCLASS()
class PERSONALGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();


	UFUNCTION(BlueprintCallable)
	void TravelToActor(class AActor * ActorToTravelTo);

	FMoveCompletedSuccessSignature EnemyAIController_MoveCompletedSuccess;

protected:

	UPROPERTY(EditAnywhere)
	class AActor * ActorToTravelTo;

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
};
