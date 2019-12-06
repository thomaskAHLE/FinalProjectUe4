// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnemyAttackComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAIController::StaticClass();
	EnemyLogicComponent = CreateDefaultSubobject <UEnemyLogicComponent>("Logic Component");
	HeadCollisionSphere = CreateDefaultSubobject<USphereComponent>("Head Sphere Collision");
	HeadCollisionSphere->SetupAttachment(this->GetMesh());
	this->GetCapsuleComponent()->ComponentTags.Add(BodyCollisionTag);
	HeadCollisionSphere->ComponentTags.Add(HeadCollisionTag);
	EnemyLogicComponent->OnDie.AddDynamic(this, &AEnemyAICharacter::Die);
	EnemyLogicComponent->OnPostTookDamage.AddDynamic(this, &AEnemyAICharacter::EndOnShot);
	EnemyLogicComponent->OnAttack.AddDynamic(this, &AEnemyAICharacter::Attack);


	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
}

void AEnemyAICharacter::Attack_Implementation(class AActor* ActorToAttack, float DamageToDeal)
{
	if (EnemyAttackComponent != nullptr)
	{
		EnemyAttackComponent->Attack(ActorToAttack, DamageToDeal, AttackStartPos);
	}
}

void AEnemyAICharacter::OnShot_Implementation(float Damage, FVector HitLocation, const TArray<FName> & ComponentTags)
{
	UE_LOG(LogTemp, Error, TEXT("Damage taken %f"), Damage);
	if (IsMoving_Implementation())
	{
		StopMoving();
	}
	if (ComponentTags.Num() > 0)
	{
		if (ComponentTags.Find(FName(HeadCollisionTag)) != INDEX_NONE)
		{
			EnemyLogicComponent->TakeDamageFromPlayer(Damage * HeadShotMultiplier);
		}
		else
		{
			EnemyLogicComponent->TakeDamageFromPlayer(Damage);
		}
	}
}

bool AEnemyAICharacter::IsMoving_Implementation()
{
	return bIsMoving;
}

bool AEnemyAICharacter::IsAttacking_Implementation()
{
	return EnemyLogicComponent->GetIsAttacking();
}

bool AEnemyAICharacter::IsDead_Implementation()
{
	return EnemyLogicComponent->GetIsDead();
}

float AEnemyAICharacter::GetEnemyVelocity_Implementation()
{
	FVector Velocity = GetVelocity();
	return sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);
}

bool AEnemyAICharacter::WasDamaged_Implementation()
{
	return EnemyLogicComponent->GetWasShot();
}

void AEnemyAICharacter::Die_Implementation()
{
	if (OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AEnemyAICharacter::DestroyWrapper, DelayAfterDeathTime, false);
}


UEnemyLogicComponent * AEnemyAICharacter::GetLogicComponent()
{
	return EnemyLogicComponent;
}

void AEnemyAICharacter::StartAttacking_Implementation()
{
	bIsMoving = false;
	bWasMoving = false;
	EnemyLogicComponent->StartAttackingLoop();
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsMoving = false;
	EnemyAttackComponent = NewObject<UEnemyAttackComponent>(this, EnemyAttackComponentType);
	if (EnemyAttackComponent != nullptr)
	{
		EnemyAttackComponent->RegisterComponent();
	}
	AIController = Cast<AEnemyAIController>(GetController());
	AIController->EnemyAIController_MoveCompletedSuccess.AddDynamic(this, &AEnemyAICharacter::StartAttacking);
	
}

void AEnemyAICharacter::EndOnShot()
{
	if (bWasMoving)
	{
		StartMoving();
	}
}

void AEnemyAICharacter::StopMoving()
{
	if (IsMoving_Implementation())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI should stop moving"))
		bWasMoving = true;
		bIsMoving = false;
		if (AIController != nullptr)
		{
			AIController->StopMovement();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI didn't stop moving"));
	}
}

void AEnemyAICharacter::StartMoving()
{
	if (!bIsMoving && bWasMoving)
	{
		bIsMoving = true;
		bWasMoving = false;
		
		if (AIController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Has Controller"));
			if (ActorToMoveTo == nullptr)
			{
				ActorToMoveTo = GetWorld()->GetFirstPlayerController()->GetPawn();
			}
			AIController->TravelToActor(ActorToMoveTo);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s can't stop moving because there isn't a controller"), *GetName())
		}
	}
}

void AEnemyAICharacter::DestroyWrapper()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}




