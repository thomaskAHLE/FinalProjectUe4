// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLogicComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "EnemyAttackComponent.h"

// Sets default values for this component's properties
UEnemyLogicComponent::UEnemyLogicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyLogicComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	EnemyAttackComponent = NewObject<UEnemyAttackComponent>(GetOwner(), EnemyAttackComponentType);
	if (EnemyAttackComponentType != nullptr)
	{
		EnemyAttackComponent->RegisterComponent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not generate enemy attack component for "), *GetName());
	}
	if (ActorToAttack == nullptr)
	{
		ActorToAttack = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	if (ActorToAttack != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has Actor To Attack"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Has No Actor To Attack"))
	}
}


void UEnemyLogicComponent::AttackPlayer()
{
	bIsAttacking = true;
	if (ActorToAttack != nullptr)
	{
		if (OnAttack.IsBound())
		{
			OnAttack.Broadcast(ActorToAttack, DamageCaused);
		}
		if (EnemyAttackComponent != nullptr)
		{
			EnemyAttackComponent->Attack(ActorToAttack, DamageCaused, StartAttackPosition);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no actor To attack"), *GetName());
	}
	bIsAttacking = false;
}


void UEnemyLogicComponent::StartAttackingLoop()
{
	bStartedAttackingLoop = true;
	bIsAttacking = true;
	UE_LOG(LogTemp, Error, TEXT("Start Attacking Timer"))
	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, this, &UEnemyLogicComponent::AttackPlayer, DelayBetweenAttacks, true, 1.f);
}

void UEnemyLogicComponent::TakeDamageFromPlayer(float Damage /*=1.f*/)
{
	if (!bIsDead)
	{
		bWasShot = true;
		CurrentHealth -= Damage;
		if (bStartedAttackingLoop)
		{
			bIsAttacking = false;
			GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandle);
		}
		if (CurrentHealth <= 0)
		{
			Die();
		}
		else
		{
			if (OnTookDamage.IsBound())
			{
				OnTookDamage.Broadcast(Damage);
			}
			GetWorld()->GetTimerManager().SetTimer(ShotDelayTimerHandle, this, &UEnemyLogicComponent::PostTookDamageFromPlayer, DelayAfterShotTime, false);
		}
	}
}

void UEnemyLogicComponent::StopAttackingLoop()
{
	bStartedAttackingLoop = false;
	GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandle);
}

void UEnemyLogicComponent::UpdateAttackStartPosition(FVector AttackStartPosition)
{
	StartAttackPosition = AttackStartPosition;
}

bool UEnemyLogicComponent::GetIsDead() const 
{
	return bIsDead;
}

bool UEnemyLogicComponent::GetWasShot() const
{
	return bWasShot;
}

bool UEnemyLogicComponent::GetIsAttacking() const
{
	return bIsAttacking;
}

void UEnemyLogicComponent::PostTookDamageFromPlayer()
{
	bWasShot = false;
	if (OnPostTookDamage.IsBound())
	{
		OnPostTookDamage.Broadcast();
	}
	if (bStartedAttackingLoop)
	{
		StartAttackingLoop();
	}
}

void UEnemyLogicComponent::Die()
{
	UE_LOG(LogTemp, Error, TEXT("Dead"));
	if (!bIsDead)
	{
		bIsDead = true;
		bIsAttacking = false;
		bWasShot = false;
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		if (OnDie.IsBound())
		{
			OnDie.Broadcast();
		}
	}
}


