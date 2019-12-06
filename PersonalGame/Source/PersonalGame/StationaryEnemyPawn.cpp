// Fill out your copyright notice in the Description page of Project Settings.


#include "StationaryEnemyPawn.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnemyLogicComponent.h"

#include "Engine/World.h"

// Sets default values
AStationaryEnemyPawn::AStationaryEnemyPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	this->SetRootComponent(CapsuleComponent);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(CapsuleComponent);
	Mesh->ComponentTags.Add(BodyCollisionTag);
	HeadCollisionComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	HeadCollisionComponent->SetupAttachment(Mesh);
	HeadCollisionComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	HeadCollisionComponent->ComponentTags.Add(HeadCollisionTag);

	EnemyLogicComponent = CreateDefaultSubobject<UEnemyLogicComponent>("LogicComponent");
	EnemyLogicComponent->OnDie.AddDynamic(this, &AStationaryEnemyPawn::Die);
	EnemyLogicComponent->OnAttack.AddDynamic(this, &AStationaryEnemyPawn::Attack);
}

void AStationaryEnemyPawn::Die_Implementation()
{
	CapsuleComponent->SetGenerateOverlapEvents(false);
	if (OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AStationaryEnemyPawn::DestroyWrapper, DelayAfterDeathTime, false);
}

void AStationaryEnemyPawn::StartAttacking_Implementation()
{
	EnemyLogicComponent->UpdateAttackStartPosition(AttackStartPos);
	EnemyLogicComponent->StartAttackingLoop();
}

bool AStationaryEnemyPawn::WasDamaged_Implementation()
{
	return EnemyLogicComponent->GetWasShot();
}

bool AStationaryEnemyPawn::IsDead_Implementation()
{
	return EnemyLogicComponent->GetIsDead();
}

float AStationaryEnemyPawn::GetEnemyVelocity_Implementation()
{
	return 0.f;
}

bool AStationaryEnemyPawn::IsAttacking_Implementation()
{
	return EnemyLogicComponent->GetIsAttacking();
}

bool AStationaryEnemyPawn::IsMoving_Implementation()
{
	return false;
}

void AStationaryEnemyPawn::Attack_Implementation(class AActor* ActorToAttack, float DamageToDeal)
{

}

void AStationaryEnemyPawn::OnShot_Implementation(float Damage, FVector HitLocation, const TArray<FName> &ComponentTags)
{
	if (ComponentTags.Num() > 0 && ComponentTags.Find(FName(HeadCollisionTag)) != INDEX_NONE)
	{
		EnemyLogicComponent->TakeDamageFromPlayer(Damage * HeadShotMultiplier);
	}
	else
	{
		EnemyLogicComponent->TakeDamageFromPlayer(Damage);
	}
}

// Called when the game starts or when spawned
void AStationaryEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AStationaryEnemyPawn::DestroyWrapper()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}

// Called every frame
void AStationaryEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

