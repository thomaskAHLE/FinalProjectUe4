// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootableInterface.h"
#include "EnemyProjectileActor.generated.h"

UCLASS()
class PERSONALGAME_API AEnemyProjectileActor : public AActor, public IShootableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectileActor();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
	void OnShot(float Damage, FVector HitLocation, const TArray<FName> &ComponentTags);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent * ProjectileFX;
	UPROPERTY(EditAnywhere)
	class USphereComponent * ProjectileSphere;
	UPROPERTY(EditAnywhere)
	float DamageToDeal;
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier;
	bool bMoveProjectileAlongSpline;
	class USplineComponent * ArcSpline;
	float CurrentDistanceAlongSpline;
	void MoveAlongSpline(float DeltaDistance);

	UPROPERTY(EditAnywhere)
	float AdditionalHeightAboveSplineAtMidPoint = 60.f;
	AActor * TargetActor;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetTargetAndStartProjectile(AActor * Target);
	UFUNCTION()
	void OnProjectileOverlap(AActor * OverlappedActor, AActor * OtherActor);

};
