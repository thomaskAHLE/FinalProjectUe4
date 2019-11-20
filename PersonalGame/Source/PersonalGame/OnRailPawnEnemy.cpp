// Fill out your copyright notice in the Description page of Project Settings.



#include "OnRailPawnEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "OnRailSplineActor.h"
#include "GameFramework/PlayerController.h"
#include "OnRailPawnPlayer.h"
#include "Engine/World.h"


AOnRailPawnEnemy::AOnRailPawnEnemy()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Enemy Mesh");
	SkeletalMesh->SetupAttachment(RootComponent);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collision Capsule");
	CollisionCapsule->SetupAttachment(SkeletalMesh);

	CollisionCapsule->SetGenerateOverlapEvents(true);
}

void AOnRailPawnEnemy::OnShot_Implementation()
{
	if (!bIsDead)
	{
		UE_LOG(LogTemp, Error, TEXT("On Shot"))
			bWasShot = true;
		--CurrentHealth;
		if (RailToFollow != nullptr && RailToFollow->IsMoving())
		{
			RailToFollow->StopMoving();
		}
		if (bStartedAttackingLoop)
		{
			bIsAttacking = false;
			GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandle);
		}
		//Play animation or something
		if (CurrentHealth <= 0)
		{
			Die();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(ShotDelayTimerHandle, this, &AOnRailPawnEnemy::EndOnShot, DelayAfterShotTime, false);
		}
	}
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

void AOnRailPawnEnemy::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	
	//I Hate this implementation, but I can't think of a better way right now.
	UWorld const * World = GetWorld();
	if (World != nullptr)
	{
		APlayerController * PC = World->GetFirstPlayerController();
		if (PC != nullptr)
		{
			AOnRailPawnPlayer * Player = Cast<AOnRailPawnPlayer>(PC->GetPawn());
			if (Player)
			{
				Player->Take_Damage();
			}
		}
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

void AOnRailPawnEnemy::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Dying"))
	bIsDead = true;
	bIsAttacking = false;
	bWasShot = false;
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AOnRailPawnEnemy::DestroyWrapper, DelayAfterDeathTime, false);
}

void AOnRailPawnEnemy::DestroyWrapper()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}
