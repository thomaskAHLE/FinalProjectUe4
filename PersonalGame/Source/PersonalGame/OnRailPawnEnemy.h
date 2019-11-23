// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnRailPawn.h"
#include "ShootableInterface.h"
#include "EnemyInterface.h"
#include "OnRailPawnEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PERSONALGAME_API AOnRailPawnEnemy : public AOnRailPawn, public IShootableInterface, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AOnRailPawnEnemy();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
	void OnShot(float Damage);
	virtual void OnShot_Implementation(float Damage) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Enemy")
		void Attack();

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



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EndOnShot();

	void StartAttacking();

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent * SkeletalMesh;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent * CollisionCapsule;

	UPROPERTY(EditAnywhere)
	int MaxHealth = 10;
	UPROPERTY(VisibleAnywhere, Category=State)
	int CurrentHealth = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bWasShot = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bIsDead = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, Category=Timer)
	float DelayBetweenAttacks = 1.f;

	UPROPERTY(EditAnywhere, Category=Timer)
		float DelayAfterShotTime = 1.f;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 3.f;


	FTimerHandle AttackDelayTimerHandle;

	FTimerHandle ShotDelayTimerHandle;

	FTimerHandle DeathDelayTimerHandle;

	UFUNCTION()
		void DestroyWrapper();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=State)
	bool bStartedAttackingLoop = false;
};
