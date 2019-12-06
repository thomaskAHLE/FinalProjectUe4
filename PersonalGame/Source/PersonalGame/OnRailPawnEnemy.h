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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRailEnemyDieSignature);
UCLASS(Abstract)
class PERSONALGAME_API AOnRailPawnEnemy : public AOnRailPawn, public IShootableInterface, public IEnemyInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnRailEnemyDieSignature OnDie;

	AOnRailPawnEnemy();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
	void OnShot(float Damage, FVector HitLocation,const TArray<FName>& ComponentTags);

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float HeadShotMultiplier = 2.f;

	UFUNCTION(BlueprintCallable)
	void EndOnShot();

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent * SkeletalMesh;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent * CollisionCapsule;

	UPROPERTY(EditAnywhere)
	class USphereComponent * HeadCollisionSphere;


	UPROPERTY(VisibleAnywhere)
	class UEnemyLogicComponent * EnemyLogicComponent;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 2.6f;

	FTimerHandle DeathDelayTimerHandle;

	bool bStartedAttacking;

	UFUNCTION(BlueprintCallable)
	void StartMoving();

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	UPROPERTY(BlueprintReadWrite)
	FVector AttackStartPos = FVector(0.f, 0.f, 0.f);

	UFUNCTION()
	void DestroyWrapper();

	FName HeadCollisionTag = "Head";
	FName BodyCollisionTag = "Body";

};
