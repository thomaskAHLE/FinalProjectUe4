// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailPawn.h"
#include "OnRailSplineActor.h"

// Sets default values
AOnRailPawn::AOnRailPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
}

float AOnRailPawn::GetCurrentVelocity() const
{
	if (RailToFollow != nullptr)
	{
		return RailToFollow->GetCurrentSpeedMultiplier();
	}
	return 0.f;
}

void AOnRailPawn::SetPawnSpeedMultiplier(float SpeedMultiplier)
{
	if (0.f < SpeedMultiplier)
	{
		PawnSpeedMultiplier = SpeedMultiplier;
		if (RailToFollow != nullptr)
		{
			RailToFollow->SetTravelerSpeedMultiplier(PawnSpeedMultiplier);
		}
	}
}

// Called when the game starts or when spawned
void AOnRailPawn::BeginPlay()
{
	Super::BeginPlay();
	if (RailToFollow != nullptr)
	{
		if (!bStartMovingOnBeginPlay)
		{
			StopPawnMoving();
		}
		RailToFollow->SetTravelerSpeedMultiplier(PawnSpeedMultiplier);
		FVector NewPos = RailToFollow->GetCurrentLocation();
		if (bUpdateRotationWithSpline)
		{
			FRotator NewRot = RailToFollow->GetCurrentRotation();
			SetActorLocationAndRotation(MoveTemp(NewPos), MoveTemp(NewRot));
		}
		else
		{
			SetActorLocation(NewPos);
		}
	}
}

// Called every frame
void AOnRailPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RailToFollow != nullptr && RailToFollow->IsMoving())
	{
		FVector NewPos = RailToFollow->GetCurrentLocation();
		if (bUpdateRotationWithSpline)
		{
			FRotator NewRot = RailToFollow->GetCurrentRotation();
			SetActorLocationAndRotation(MoveTemp(NewPos), MoveTemp(NewRot));
		}
		else
		{
			SetActorLocation(NewPos);
		}
	}
}

void AOnRailPawn::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	if (RailToFollow != nullptr)
	{
		if (LastIndex != EDITOR_ONLY_SplinePointIdxToMoveTo)
		{
			EDITOR_ONLY_bMovePawnToIndex = true;
			LastIndex = EDITOR_ONLY_SplinePointIdxToMoveTo;
		}
		if (!FMath::IsNearlyEqual(EDITOR_ONLY_DistanceAlongSpline, LastDistance))
		{
			EDITOR_ONLY_bMovePawnToDistance = true;
			LastDistance = EDITOR_ONLY_DistanceAlongSpline;
		}
		if (EDITOR_ONLY_bMovePawnToDistance)
		{
			if (bUpdateRotationWithSpline)
			{
				SetActorLocationAndRotation(RailToFollow->GetPosAtDis(EDITOR_ONLY_DistanceAlongSpline), RailToFollow->GetRotAtDis(EDITOR_ONLY_DistanceAlongSpline));		
			}
			else
			{
				SetActorLocation(RailToFollow->GetPosAtDis(EDITOR_ONLY_DistanceAlongSpline));
			}
			EDITOR_ONLY_bMovePawnToDistance = false;
		}
		if (EDITOR_ONLY_bMovePawnToIndex)
		{
			if (bUpdateRotationWithSpline)
			{
				SetActorLocationAndRotation(RailToFollow->GetPosAtIdx(EDITOR_ONLY_SplinePointIdxToMoveTo), RailToFollow->GetRotAtIdx(EDITOR_ONLY_SplinePointIdxToMoveTo));
			}
			else
			{
				SetActorLocation(RailToFollow->GetPosAtIdx(EDITOR_ONLY_SplinePointIdxToMoveTo));
			}
		}
		EDITOR_ONLY_bMovePawnToIndex = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Rail to follow"))
	}
#endif
}

void AOnRailPawn::StartPawnMoving()
{
	if (RailToFollow != nullptr && !RailToFollow->HasReachedEndOfRail())
	{
		RailToFollow->StartMoving();
	}
}

void AOnRailPawn::StopPawnMoving()
{
	if (RailToFollow != nullptr)
	{
		RailToFollow->StopMoving();
	}
}

void AOnRailPawn::SetRailToFollow(AOnRailSplineActor * Rail)
{
	if (Rail != nullptr)
	{
		RailToFollow = Rail;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Rail is nullptr"))
	}
}

