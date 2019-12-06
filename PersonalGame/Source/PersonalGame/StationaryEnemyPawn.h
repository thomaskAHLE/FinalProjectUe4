// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShootableInterface.h"
#include "EnemyInterface.h"
#include "StationaryEnemyPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStationaryEnemyDieSignature);
UCLASS()
class PERSONALGAME_API AStationaryEnemyPawn : public APawn, public IShootableInterface, public IEnemyInterface
{

	GENERATED_BODY()
public:
		// Sets default values for this actor's properties
		AStationaryEnemyPawn();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
		void OnShot(float Damage, FVector HitLocation, const TArray<FName> &ComponentTags);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Enemy")
		void Attack(class AActor* ActorToAttack, float DamageToDeal);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Enemy")
		void Die();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyState")
		bool IsMoving();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyState")
		bool IsAttacking();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyState")
		float GetEnemyVelocity();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyState")
		bool IsDead();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyState")
		bool WasDamaged();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Enemy")
		void StartAttacking();

	UPROPERTY(BlueprintAssignable)
		FOnStationaryEnemyDieSignature OnDie;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class USphereComponent * HeadCollisionComponent;
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent * CapsuleComponent;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent * Mesh;
	UPROPERTY(VisibleAnywhere)
		class UEnemyLogicComponent * EnemyLogicComponent;


	UPROPERTY(EditAnywhere, Category = Timer)
		float DelayAfterDeathTime = 2.6f;

	UPROPERTY(EditAnywhere)
		float HeadShotMultiplier = 2.f;

	FTimerHandle DeathDelayTimerHandle;

	UPROPERTY(BlueprintReadWrite)
		FVector AttackStartPos = FVector(0.f, 0.f, 0.f);

	UFUNCTION()
		void DestroyWrapper();

	FName HeadCollisionTag = "Head";
	FName BodyCollisionTag = "Body";

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
