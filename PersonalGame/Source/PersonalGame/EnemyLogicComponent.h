// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyLogicComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDieSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTookDamageSignature, float /*Damage*/, Damage);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPostTookDamageSignature);





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONALGAME_API UEnemyLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyLogicComponent();

	void StartAttackingLoop();

	UPROPERTY(BlueprintAssignable)
	mutable FDieSignature EnemyLogicComponent_Die;

	UPROPERTY(BlueprintAssignable)
	mutable FOnTookDamageSignature EnemyLogicComponent_TookDamage;
	
	UPROPERTY(BlueprintAssignable)
	mutable FPostTookDamageSignature EnemyLogicComponent_PostTookDamage;

	UFUNCTION()
	void TakeDamageFromPlayer(float Damage = 1.f);

	UFUNCTION()
	void StopAttackingLoop();

	/*Getters*/
	bool GetIsDead() const ;
	bool GetWasShot() const ;
	bool GetIsAttacking() const;

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
		float DelayBetweenAttacks = 2.6f;

	UPROPERTY(EditAnywhere, Category = Timer)
		float DelayAfterShotTime = 2.6f;

	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayAfterDeathTime = 3.f;

	UPROPERTY(EditAnywhere, Category = Damage)
	float DamageCaused = 1.f;
	
	UFUNCTION()
	void AttackPlayer();

	FTimerHandle AttackDelayTimerHandle;

	FTimerHandle ShotDelayTimerHandle;

	FTimerHandle DeathDelayTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bStartedAttackingLoop = false;

	//nullptr by default, unless assigned, it will be assigned to the player pawn
	UPROPERTY(EditAnywhere, Category=Target)
	class AActor * ActorToAttack = nullptr;

	UFUNCTION()
	void PostTookDamageFromPlayer();

	UFUNCTION()
	void Die();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
