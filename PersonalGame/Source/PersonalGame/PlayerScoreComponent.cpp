// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScoreComponent.h"
#include "Engine/World.h"

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
	++HitStreak;
}

void UPlayerScoreComponent::ResetScoreComponent()
{
	HitStreak = 0;
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

void UPlayerScoreComponent::ResetHitStreak()
{
	HitStreak = 0;
}

float UPlayerScoreComponent::GetTimePlayed() const
{
	return StartTime < EndTime ? EndTime - StartTime : GetWorld()->GetTimeSeconds() - StartTime;
}

float UPlayerScoreComponent::GetScoreDamageMultiplier() const
{

	if (HitStreak < StreakRequiredToFirstDamageMultiplier)
	{
		UE_LOG(LogTemp, Error, TEXT("Using base damage multiplier"));
		return BaseDamageMultiplierValue;
	}
	else if (HitStreak < StreakRequiredToSecondDamageMultiplier)
	{
		UE_LOG(LogTemp, Error, TEXT("Using first damage multiplier"));
		return FirstDamageMultiplierValue;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Using second damage multiplier"));
		return SecondDamageMultiplierValue;
	}
}

// Called when the game starts
void UPlayerScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	ResetScoreComponent();
}


