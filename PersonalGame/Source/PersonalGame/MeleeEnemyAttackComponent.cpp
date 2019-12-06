// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAttackComponent.h"
#include "GameFramework/Controller.h"


void UMeleeEnemyAttackComponent::Attack(class AActor* ActorToAttack, float DamageToDeal, FVector AttackBeginPos)
{
	Super::Attack(ActorToAttack, DamageToDeal, AttackBeginPos);
	FDamageEvent DamageEvent;
	AController * MyController = nullptr;
	if (GetOwner() != nullptr)
	{
		MyController = GetOwner()->GetInstigatorController();
	}
	ActorToAttack->TakeDamage(DamageToDeal, DamageEvent, MyController, GetOwner());
	UE_LOG(LogTemp, Error, TEXT("Attacking player"));
}
