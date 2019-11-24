// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include "EnemyAIController.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyAIController::StaticClass();
	EnemyLogicComponent = CreateDefaultSubobject <UEnemyLogicComponent>("Logic Component");
}




void AEnemyAICharacter::OnShot_Implementation(float Damage)
{

}

bool AEnemyAICharacter::IsMoving_Implementation()
{
	return true;
}

bool AEnemyAICharacter::IsAttacking_Implementation()
{
	return bIsAttacking;
}

bool AEnemyAICharacter::IsDead_Implementation()
{
	return bIsDead;
}

float AEnemyAICharacter::GetEnemyVelocity_Implementation()
{
	return 0.f;
}

bool AEnemyAICharacter::WasDamaged_Implementation()
{
	return bWasDamaged;
}

void AEnemyAICharacter::Die_Implementation()
{
	
}

void AEnemyAICharacter::Attack_Implementation()
{
	
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	MyController = Cast<AEnemyAIController>(GetController());
	if (MyController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has Controller"));
		if (ActorToMoveTo != nullptr)
		{
			MyController->TravelToActor(ActorToMoveTo);
		}
	}
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



