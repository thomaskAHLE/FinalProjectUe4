// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Engine/TargetPoint.h"


AEnemyAIController::AEnemyAIController()
{

}

void AEnemyAIController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin play enemy ai controller"))
	Super::BeginPlay();
	if (ActorToTravelTo != nullptr)
	{
		TravelToActor(ActorToTravelTo);
	}
}

void AEnemyAIController::TravelToPoint(ATargetPoint * NextPointToTravelTo)
{
	TravelToActor(NextPointToTravelTo);
}

void AEnemyAIController::TravelToActor( AActor * ActorToTravelTo)
{
	MoveToActor(ActorToTravelTo);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	UE_LOG(LogTemp, Warning, TEXT("Move completed"));
}

