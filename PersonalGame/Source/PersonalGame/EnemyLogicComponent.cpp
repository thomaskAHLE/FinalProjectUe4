// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLogicComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"

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
	if (ActorToAttack == nullptr)
	{
		ActorToAttack = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}


void UEnemyLogicComponent::AttackPlayer()
{
	if (ActorToAttack != nullptr)
	{
		FDamageEvent DamageEvent;
		AController * MyController = nullptr;
		if (GetOwner() != nullptr)
		{
			MyController = GetOwner()->GetInstigatorController();
		}
		ActorToAttack->TakeDamage(DamageCaused, DamageEvent, MyController, GetOwner());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no actor To attack"), *GetName());
	}
}

void UEnemyLogicComponent::StartAttackingLoop()
{
	bStartedAttackingLoop = true;
	
}

void UEnemyLogicComponent::TakeDamageFromPlayer(float Damage /*=1.f*/)
{
	UE_LOG(LogTemp, Error, TEXT("On Shot"))
		bWasShot = true;
	--CurrentHealth;
	
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
		GetWorld()->GetTimerManager().SetTimer(ShotDelayTimerHandle, this, &UEnemyLogicComponent::EndTookDamageFromPlayer, DelayAfterShotTime, false);
	}
}

void UEnemyLogicComponent::EndTookDamageFromPlayer()
{

}

void UEnemyLogicComponent::Die()
{
}



// Called every frame
void UEnemyLogicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

