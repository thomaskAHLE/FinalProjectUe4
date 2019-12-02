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
	EnemyLogicComponent->EnemyLogicComponent_PostTookDamage.AddDynamic(this, &AOnRailPawnEnemy::EndOnShot);
}

void AOnRailPawnEnemy::OnShot_Implementation(float Damage)
{
	if (RailToFollow != nullptr && !RailToFollow->HasReachedEndOfRail())
	{
		RailToFollow->StopMoving();
	}
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
	return EnemyLogicComponent->GetIsDead();
}

bool AOnRailPawnEnemy::WasDamaged_Implementation()
{
	
	return EnemyLogicComponent->GetWasShot();
}

void AOnRailPawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (RailToFollow != nullptr)
	{
		RailToFollow->EndOfSplineSignature.AddDynamic(this, &AOnRailPawnEnemy::Attack);
	}
	
}

void AOnRailPawnEnemy::Attack_Implementation()
{
	bStartedAttacking = true;
	if (EnemyLogicComponent != nullptr)
	{
		EnemyLogicComponent->StartAttackingLoop();
	}
}

void AOnRailPawnEnemy::EndOnShot()
{
	if (RailToFollow != nullptr && !RailToFollow->HasReachedEndOfRail())
	{
		RailToFollow->StartMoving();
	}
}

void AOnRailPawnEnemy::Die_Implementation()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AOnRailPawnEnemy::DestroyWrapper, DelayAfterDeathTime, false);
}

bool AOnRailPawnEnemy::IsAttacking_Implementation()
{
	return EnemyLogicComponent->GetIsAttacking();
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
