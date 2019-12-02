// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScoreComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UPlayerScoreComponent::UPlayerScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


int32 UPlayerScoreComponent::GetTotalShots() const
{
	return TotalShots;
}

int32 UPlayerScoreComponent::GetNumberHit() const
{
	return NumberHit;
}


int32 UPlayerScoreComponent::GetNumberKilled() const
{
	return NumberKilled;
}

void UPlayerScoreComponent::IncrementTotalShots()
{
	UE_LOG(LogTemp, Warning, TEXT("Incrementing Total Shots"))
	++TotalShots;
}

void UPlayerScoreComponent::IncrementNumKilled()
{
	++NumberKilled;
}

void UPlayerScoreComponent::IncrementNumHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Incrementing Number Hit"))
	++NumberHit;
}

void UPlayerScoreComponent::ResetScoreComponent()
{
	TotalShots = 0;
	NumberHit = 0;
	NumberKilled = 0;
	EndTime = 0.f;
	StartTime = GetWorld()->GetTimeSeconds();
}

void UPlayerScoreComponent::StopTime()
{
	EndTime = GetWorld()->GetTimeSeconds();
}

float UPlayerScoreComponent::GetTimePlayed() const
{
	return StartTime < EndTime ? EndTime - StartTime : GetWorld()->GetTimeSeconds() - StartTime;
}

// Called when the game starts
void UPlayerScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	ResetScoreComponent();
}


// Called every frame
void UPlayerScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

