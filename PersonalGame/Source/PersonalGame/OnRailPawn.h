// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OnRailPawn.generated.h"

UCLASS()
class PERSONALGAME_API AOnRailPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOnRailPawn();

	UPROPERTY(EditAnywhere)
	class AOnRailSplineActor * RailToFollow;

	UFUNCTION(BlueprintCallable)
	float GetCurrentVelocity() const;

	UFUNCTION(BlueprintCallable)
	void SetPawnSpeedMultiplier(float SpeedMultiplier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	bool bUpdateRotationWithSpline = true;
	
	//Set to change speed of instanced pawn
	UPROPERTY(EditAnywhere)
	float PawnSpeedMultiplier = 1.f;

	UPROPERTY(EditAnywhere)
		bool bStartMovingOnBeginPlay = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void StartPawnMoving();

	UFUNCTION(BlueprintCallable)
	void StopPawnMoving();

	UFUNCTION(BlueprintCallable)
	void SetRailToFollow(class AOnRailSplineActor * Rail);

private:
	// Allows changing pawn position on spline in the editor to get a better view of how it should look
// only use in on construction

	float LastDistance = 0.f;
	
	int32 LastIndex = 0;

	//Point in spline at index
	UPROPERTY(EditAnywhere, Category = EditorOnly)
	int32 EDITOR_ONLY_SplinePointIdxToMoveTo = 0;

	//Point in spline at index 
	UPROPERTY(EditAnywhere, Category = EditorOnly)
	float EDITOR_ONLY_DistanceAlongSpline = 0.f;

	//Click to move pawn to the specified index
	UPROPERTY(EditAnywhere, Category = EditorOnly)
	bool EDITOR_ONLY_bMovePawnToIndex = false;

	//Click to move pawn to specified distance
	UPROPERTY(EditAnywhere, Category=EditorOnly)
	bool EDITOR_ONLY_bMovePawnToDistance = false;
};
