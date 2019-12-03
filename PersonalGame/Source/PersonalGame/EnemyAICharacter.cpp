// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAIController::StaticClass();
	EnemyLogicComponent = CreateDefaultSubobject <UEnemyLogicComponent>("Logic Component");
	EnemyLogicComponent->EnemyLogicComponent_Die.AddDynamic(this, &AEnemyAICharacter::Die);
	EnemyLogicComponent->EnemyLogicComponent_PostTookDamage.AddDynamic(this, &AEnemyAICharacter::EndOnShot);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
}




void AEnemyAICharacter::OnShot_Implementation(float Damage)
{
	if (bIsMoving)
	{
		StopMoving();
	}
	EnemyLogicComponent->TakeDamageFromPlayer(Damage);
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
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle, this, &AEnemyAICharacter::DestroyWrapper, DelayAfterDeathTime, false);
}

void AEnemyAICharacter::Attack_Implementation()
{
	EnemyLogicComponent->StartAttackingLoop();
}

UEnemyLogicComponent * AEnemyAICharacter::GetLogicComponent()
{
	return EnemyLogicComponent;
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AEnemyAIController>(GetController());
	if (AIController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has Controller"));
		if (ActorToMoveTo == nullptr)
		{
			ActorToMoveTo = GetWorld()->GetFirstPlayerController()->GetPawn();
		}
		AIController->TravelToActor(ActorToMoveTo);
		AIController->EnemyAIController_MoveCompletedSuccess.AddDynamic(this, &AEnemyAICharacter::Attack);

	}
	bIsMoving = true;
	StartMoving();
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

	if (bIsMoving)
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
	if (!bIsMoving)
	{
		bIsMoving = true;
		bWasMoving = false;
		AIController->TravelToActor(ActorToMoveTo);
	}
}

void AEnemyAICharacter::DestroyWrapper()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}




