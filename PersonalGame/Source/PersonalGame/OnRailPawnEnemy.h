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

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent * SkeletalMesh;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent * CollisionCapsule;

	UPROPERTY(VisibleAnywhere)
	class UEnemyLogicComponent * EnemyLogicComponent;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 2.6f;

	FTimerHandle DeathDelayTimerHandle;

	bool bStartedAttacking;

	UFUNCTION()
	void DestroyWrapper();
};
