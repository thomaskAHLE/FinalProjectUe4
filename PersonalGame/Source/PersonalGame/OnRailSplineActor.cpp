// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailSplineActor.h"
#include "Components/SplineComponent.h"

// Sets default values
AOnRailSplineActor::AOnRailSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RailSpline = CreateDefaultSubobject<USplineComponent>("RailSpline");
	RootComponent = RailSpline;

}

void AOnRailSplineActor::OnConstruction(const FTransform& Transform)
{
	#if WITH_EDITOR
	//Want to make sure spline point and should stop array are the same size
	//If there is a change in size, resize array and default all stops to false
	if (NumberSplinePoints != RailSpline->GetNumberOfSplinePoints())
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed Number of Spline Points"));
		NumberSplinePoints = RailSpline->GetNumberOfSplinePoints();
		ShouldStopAtSplinePoint.SetNum(NumberSplinePoints, true);
		SpeedMultiplierToSplinePoint.SetNum(NumberSplinePoints, true);
		for (int32 i = 0; i < NumberSplinePoints; ++i)
		{
			ShouldStopAtSplinePoint[i] = false;
			SpeedMultiplierToSplinePoint[i] = DefaultSpeedMultiplier;
		}
	}
	if (EDITOR_ONLY_bUpdateDefaultSpeedMultiplier)
	{
		for (auto & speed : SpeedMultiplierToSplinePoint)
		{
			if (FMath::IsNearlyEqual(speed, LastDefaultSpeedMultiplier))
			{
				speed = DefaultSpeedMultiplier;
			}
		}
		LastDefaultSpeedMultiplier = DefaultSpeedMultiplier;
	}
	EDITOR_ONLY_bUpdateDefaultSpeedMultiplier = false;
	#endif
}

bool AOnRailSplineActor::IsMoving() const
{
	return bIsMoving;
}

FRotator AOnRailSplineActor::GetCurrentRotation() const
{
	return RailSpline->GetRotationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
}

FVector AOnRailSplineActor::GetCurrentLocation() const
{
	return RailSpline->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
}

void AOnRailSplineActor::StartMoving()
{
	if (!bIsMoving && !bHasReachedendOfRail)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Starting to move again"), *GetName())
		bIsMoving = true;
	}
}

void AOnRailSplineActor::StopMoving()
{
	if (bIsMoving && !bHasReachedendOfRail)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Stopped moving again"), *GetName())
		bIsMoving = false;
	}
}

bool AOnRailSplineActor::HasReachedEndOfRail() const
{
	return bHasReachedendOfRail;
}

float AOnRailSplineActor::GetCurrentSpeedMultiplier() const
{
	return CurrentSpeedMultiplier;
}

void AOnRailSplineActor::SetTravelerSpeedMultiplier(float SpeedMultiplier /*= 1.f*/)
{
	TravelingActorSpeedMultiplier = SpeedMultiplier;
}

#if WITH_EDITOR
FRotator AOnRailSplineActor::GetRotAtIdx(int32& index) const
{
	index = index < NumberSplinePoints ? index : 0;
	return RailSpline->GetRotationAtSplinePoint(index, ESplineCoordinateSpace::World);
}

FVector AOnRailSplineActor::GetPosAtIdx(int32& index) const
{
	index = index < NumberSplinePoints ? index : 0;
	return RailSpline->GetLocationAtSplinePoint(index, ESplineCoordinateSpace::World);
}

FRotator AOnRailSplineActor::GetRotAtDis(float& distance) const
{
	distance = distance < RailSpline->GetSplineLength() ? distance : RailSpline->GetSplineLength();
	return RailSpline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
}

FVector AOnRailSplineActor::GetPosAtDis(float& distance) const
{
	distance = distance < RailSpline->GetSplineLength() ? distance : RailSpline->GetSplineLength();
	return RailSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
}
#endif

// Called when the game starts or when spawned
void AOnRailSplineActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentSplinePointIdx = 0;
	NumberSplinePoints = RailSpline->GetNumberOfSplinePoints();
	NextSplinePointIdx = CurrentSplinePointIdx + 1;
	bIsMoving = !ShouldStopAtSplinePoint[CurrentSplinePointIdx];
	bHasReachedendOfRail = false;
	
}

void AOnRailSplineActor::UpdateCurrentDistance(float time)
{
	CurrentSpeedMultiplier = GetSpeedMultiplier(NextSplinePointIdx, CurrentDistance) * TravelingActorSpeedMultiplier;
	CurrentDistance += time * CurrentSpeedMultiplier;
}


float AOnRailSplineActor::GetSpeedMultiplier_Implementation(int32 TravelingToIdx, float DistanceAlongSpline)
{

	return TravelingToIdx < SpeedMultiplierToSplinePoint.Num() ? SpeedMultiplierToSplinePoint[TravelingToIdx] : DefaultSpeedMultiplier;
}

// Called every frame
void AOnRailSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsMoving)
	{
		if (CurrentDistance < RailSpline->GetDistanceAlongSplineAtSplinePoint(NextSplinePointIdx))
		{
			UpdateCurrentDistance(DeltaTime);
		}
		else
		{
			CurrentSplinePointIdx = NextSplinePointIdx;
			if (NextSplinePointIdx + 1 < NumberSplinePoints)
			{
				NextSplinePointIdx += 1;
				bIsMoving = !ShouldStopAtSplinePoint[CurrentSplinePointIdx];
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Reached end of spline %s, stopped moving"), *GetName())
				bHasReachedendOfRail = true;
				bIsMoving = false;
			}
			
		}
	}
}

