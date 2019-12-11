// Fill out your copyright notice in the Description page of Project Settings.



#include "OnRailPawnEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "OnRailPawnPlayer.h"
#include "OnRailSplineActor.h"
#include "EnemyLogicComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AOnRailPawnEnemy::AOnRailPawnEnemy()
{
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collision Capsule");
	CollisionCapsule->SetupAttachment(RootComponent);
	CollisionCapsule->SetGenerateOverlapEvents(true);
	CollisionCapsule->ComponentTags.Add(BodyCollisionTag);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Enemy Mesh");
	SkeletalMesh->SetupAttachment(CollisionCapsule);

	HeadCollisionSphere = CreateDefaultSubobject<USphereComponent>("HeadCollisionComponent");
	HeadCollisionSphere->SetupAttachment(SkeletalMesh);
	HeadCollisionSphere->SetGenerateOverlapEvents(true);
	HeadCollisionSphere->ComponentTags.Add(HeadCollisionTag);

	EnemyLogicComponent = CreateDefaultSubobject<UEnemyLogicComponent>("Logic Component");
	EnemyLogicComponent->OnDie.AddDynamic(this, &AOnRailPawnEnemy::Die);
	EnemyLogicComponent->OnAttack.AddDynamic(this, &AOnRailPawnEnemy::Attack);
	EnemyLogicComponent->OnPostTookDamage.AddDynamic(this, &AOnRailPawnEnemy::EndOnShot);
}




void AOnRailPawnEnemy::Attack_Implementation(class AActor* ActorToAttack, float DamageToDeal)
{

}

void AOnRailPawnEnemy::StartAttacking_Implementation()
{
	StopMoving();
	EnemyLogicComponent->UpdateAttackStartPosition(AttackStartPos);
	EnemyLogicComponent->StartAttackingLoop();
}


void AOnRailPawnEnemy::OnShot_Implementation(float Damage, FVector HitLocation, const TArray<FName> & ComponentTags)
{
	
	if (IsMoving_Implementation())
	{
		StopMoving();
	}
	if (ComponentTags.Num() > 0)
	{
		if (ComponentTags.Find(FName(HeadCollisionTag)) != INDEX_NONE)
		{
			UE_LOG(LogTemp, Error, TEXT("HEADSHOT!"));
			EnemyLogicComponent->TakeDamageFromPlayer(Damage * HeadShotMultiplier);
		}
		else
		{
			EnemyLogicComponent->TakeDamageFromPlayer(Damage);
		}
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
		RailToFollow->EndOfSplineSignature.AddDynamic(this, &AOnRailPawnEnemy::StartAttacking);
	}
	
}

void AOnRailPawnEnemy::EndOnShot()
{
	if (!bStartedAttacking)
	{
		StartMoving();
	}
}

void AOnRailPawnEnemy::Die_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("%s Dead"), *GetName())
	CollisionCapsule->SetGenerateOverlapEvents(false);
	if (OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
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

void AOnRailPawnEnemy::StartMoving()
{
	StartPawnMoving();
}

void AOnRailPawnEnemy::StopMoving()
{
	StopPawnMoving();
}

void AOnRailPawnEnemy::DestroyWrapper()
{
	CollisionCapsule->SetGenerateOverlapEvents(false);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}
