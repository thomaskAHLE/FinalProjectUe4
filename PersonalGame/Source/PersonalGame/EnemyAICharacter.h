// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyInterface.h"
#include "ShootableInterface.h"
#include "EnemyAICharacter.generated.h"

UCLASS()
class PERSONALGAME_API AEnemyAICharacter : public ACharacter, public IShootableInterface,  public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shootable")
	void OnShot(float Damage);

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UEnemyLogicComponent * EnemyLogicComponent;

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

	void StopMoving();
	void StartMoving();

	UFUNCTION()
	void DestroyWrapper();
};