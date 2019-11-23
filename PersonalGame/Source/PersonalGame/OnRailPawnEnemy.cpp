// Fill out your copyright notice in the Description page of Project Settings.



#include "OnRailPawnEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "OnRailPawnPlayer.h"
#include "OnRailSplineActor.h"
#include "EnemyLogicComponent.h"
#include "Engine/World.h"


AOnRailPawnEnemy::AOnRailPawnEnemy()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Enemy Mesh");
	SkeletalMesh->SetupAttachment(RootComponent);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collision Capsule");
	CollisionCapsule->SetupAttachment(SkeletalMesh);
	CollisionCapsule->SetGenerateOverlapEvents(true);
	EnemyLogicComponent = CreateDefaultSubobject<UEnemyLogicComponent>("Logic Component");
	EnemyLogicComponent->EnemyLogicComponent_Die.AddDynamic(this, &AOnRailPawnEnemy::Die);
}

void AOnRailPawnEnemy::OnShot_Implementation(float Damage)
{
	if (EnemyLogicComponent != nullptr)
	{
		EnemyLogicComponent->TakeDamageFromPlayer(Damage);
	}
}


float AOnRailPawnEnemy::GetEnemyVelocity_Implementation()
{
	return GetCurrentVelocity();
}

bool AOnRailPawnEnemy::IsDead_Implementation()
{
	return bIsDead;
}

bool AOnRailPawnEnemy::WasDamaged_Implementation()
{
	return bWasShot;
}

void AOnRailPawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bStartedAttackingLoop && RailToFollow != nullptr && RailToFollow->HasReachedEndOfRail())
	{
		bStartedAttackingLoop = true;
		UE_LOG(LogTemp, Error, TEXT("Should Start Attacking"))
		StartAttacking();
	}
}

void AOnRailPawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	bStartedAttackingLoop = false;
	
}

void AOnRailPawnEnemy::Attack_Implementation()
{
	if (EnemyLogicComponent != nullptr)
	{
		EnemyLogicComponent->AttackPlayer();
	}
}

void AOnRailPawnEnemy::EndOnShot()
{
	UE_LOG(LogTemp, Warning, TEXT("EndOnShot"))


	if (!bIsDead)
	{
		bWasShot = false;
		if (bStartedAttackingLoop)
		{
			bIsAttacking = true;
			StartAttacking();
		}
		else
		{
			if (RailToFollow != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Start Moving again"))
					RailToFollow->StartMoving();
			}
		}
	}
}

void AOnRailPawnEnemy::StartAttacking()
{
	bIsAttacking = true;
	UE_LOG(LogTemp, Error, TEXT("Start Attacking Timer"))
	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, this, &AOnRailPawnEnemy::Attack, DelayBetweenAttacks, true, 1.f);
}

void AOnRailPawnEnemy::Die_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Dying"))
	bIsDead = true;
	bIsAttacking = false;
	bWasShot = false;
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AOnRailPawnEnemy::DestroyWrapper, DelayAfterDeathTime, false);
}

bool AOnRailPawnEnemy::IsAttacking_Implementation()
{
	return bIsAttacking;
}

bool AOnRailPawnEnemy::IsMoving_Implementation()
{
	return 0.f < GetEnemyVelocity();
}

void AOnRailPawnEnemy::DestroyWrapper()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}
