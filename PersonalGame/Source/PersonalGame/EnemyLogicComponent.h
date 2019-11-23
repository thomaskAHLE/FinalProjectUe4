// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyLogicComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONALGAME_API UEnemyLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyLogicComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int MaxHealth = 10;

	UPROPERTY(VisibleAnywhere, Category = State)
		int CurrentHealth = 5;

	UPROPERTY(VisibleAnywhere, Category = State)
		bool bWasShot = false;

	UPROPERTY(VisibleAnywhere, Category = State)
		bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, Category = State)
		bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = State)
		bool bWasDamaged = false;
	UPROPERTY(EditAnywhere, Category = Timer)
		float DelayBetweenAttacks = 1.f;

	UPROPERTY(EditAnywhere, Category = Timer)
		float DelayAfterShotTime = 1.f;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 3.f;

	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageCaused = 1.f;


	FTimerHandle AttackDelayTimerHandle;

	FTimerHandle ShotDelayTimerHandle;

	FTimerHandle DeathDelayTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bStartedAttackingLoop = false;

	//nullptr by default, unless assigned, it will be assigned to the player pawn
	UPROPERTY(EditAnywhere, Category=Target)
	class AActor * ActorToAttack = nullptr;

	UFUNCTION()
	void AttackPlayer();

	UFUNCTION()
	void StartAttackingLoop();

	UFUNCTION()
	void TakeDamageFromPlayer(float Damage = 1.f);

	UFUNCTION()
	void EndTookDamageFromPlayer();

	UFUNCTION()
	void Die();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
