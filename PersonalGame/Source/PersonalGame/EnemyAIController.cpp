// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/TargetPoint.h"


AEnemyAIController::AEnemyAIController()
{

}

void AEnemyAIController::TravelToActor( AActor * ActorToTravelTo)
{
	MoveToActor(ActorToTravelTo);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result == EPathFollowingResult::Success)
	{
		if (EnemyAIController_MoveCompletedSuccess.IsBound())
		{
			UE_LOG(LogTemp, Warning, TEXT("Move completed for %s "),*GetName());
			EnemyAIController_MoveCompletedSuccess.Broadcast();
		}
	}
}

