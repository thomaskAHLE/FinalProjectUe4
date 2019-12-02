// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnRailSplineActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReachedEndOfSplineSignature);
UCLASS()
class PERSONALGAME_API AOnRailSplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOnRailSplineActor();
	
	FReachedEndOfSplineSignature EndOfSplineSignature;
	// for updating when changed in level
	virtual void OnConstruction(const FTransform& Transform) override;

	bool IsMoving() const;

	FRotator GetCurrentRotation() const;
	
	FVector GetCurrentLocation() const;

	//Callable by some other class to inform the actor that movement can continue
	//Should probably be done in level blueprint
	UFUNCTION(BlueprintCallable)
	void StartMoving();

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	bool HasReachedEndOfRail() const;

	float GetCurrentSpeedMultiplier() const;

	void SetTravelerSpeedMultiplier(float SpeedMultiplier = 1.f);
//Editor only functions allowing designer to get position and rotation along spline
#if WITH_EDITOR
	FRotator GetRotAtIdx(int32& index) const ;
	FVector GetPosAtIdx(int32& index) const ;
	FRotator GetRotAtDis(float& distance) const ;
	FVector GetPosAtDis(float& distance) const ;
#endif


protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Updates the current distance variable
	//virtual to allow child implementations to be less dumb
	virtual void UpdateCurrentDistance(float time);

	UFUNCTION(BlueprintNativeEvent)
	float GetSpeedMultiplier(int32 TravelingToIdx, float DistanceAlongSpline);

	//RootComponent spline to travel along
	UPROPERTY(EditAnywhere)
	class USplineComponent * RailSpline;
	
	//Tracks current distance along spline 
	UPROPERTY()
	float CurrentDistance = 0.f;

	UPROPERTY()
	bool bIsMoving;

	bool bHasReachedendOfRail = false;

	//The Index of the spline point we are waiting at or traveling from
	UPROPERTY()
	int32 CurrentSplinePointIdx = 0;

	//The index of the spline point we are traveling to
	UPROPERTY()
	int32 NextSplinePointIdx = 0;

	//Count of number of spline points.
	//Used in OnConstruction to determine if spline points have been added or removed 
	UPROPERTY()
	int32 NumberSplinePoints = 0;

	//Speed Multiplier
	UPROPERTY(EditAnywhere)
	float DefaultSpeedMultiplier = 100.f;

	float CurrentSpeedMultiplier = 0.f;


	//Array of booleans corresponding to the spline points
	//Determines whether reaching the spline point at the index should stop movement across the spline
	UPROPERTY(EditAnywhere)
	TArray<bool> ShouldStopAtSplinePoint;

	//Array of floats determining speed to next spline point
	// Default speed will be used unless changed else where
	UPROPERTY(EditAnywhere)
	TArray<float> SpeedMultiplierToSplinePoint;

	float TravelingActorSpeedMultiplier = 1.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	float LastDefaultSpeedMultiplier;
	
	UPROPERTY(EditAnywhere)
	bool EDITOR_ONLY_bUpdateDefaultSpeedMultiplier = false;
};
