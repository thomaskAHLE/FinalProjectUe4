// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyInterface.h"
#include "ShootableInterface.h"
#include "EnemyAICharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIEnemyDieSignature);

UCLASS(Abstract)
class PERSONALGAME_API AEnemyAICharacter : public ACharacter, public IShootableInterface,  public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

	UPROPERTY(BlueprintAssignable)
	FOnAIEnemyDieSignature OnDie;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
	void OnShot(float Damage, FVector HitLocation, const TArray<FName> & ComponentTags);

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


	UPROPERTY(EditAnywhere)
	bool bStartMovingOnBeginPlay = false;

	UPROPERTY(EditAnywhere)
	float HeadShotMultiplier = 2.f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class UEnemyLogicComponent * EnemyLogicComponent;

	UPROPERTY(EditAnywhere)
	class USphereComponent * HeadCollisionSphere;

	UPROPERTY(EditAnywhere)
	class AActor * ActorToMoveTo;

	UPROPERTY(VisibleAnywhere)
	class AEnemyAIController * AIController;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 2.6f;

	UFUNCTION()
	void EndOnShot();

	FTimerHandle DeathDelayTimerHandle;

	bool bStartedAttacking = false;

	bool bIsMoving = true;
	bool bWasMoving = false;

	UFUNCTION(BlueprintCallable)
	void StopMoving();

	UFUNCTION(BlueprintCallable)
	void StartMoving();

	UPROPERTY(BlueprintReadWrite)
	FVector AttackStartPos = FVector(0.f, 0.f, 0.f);

	UFUNCTION()
	void DestroyWrapper();

	FName HeadCollisionTag = "Head";
	FName BodyCollisionTag = "Body";
};
