// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAttackComponent.h"
#include "EnemyProjectileActor.h"
#include "Engine/World.h"

void URangedEnemyAttackComponent::Attack(class AActor* ActorToAttack, float DamageToDeal, FVector AttackBeginPos)
{
	FActorSpawnParameters SpawnParameters;
	AEnemyProjectileActor * SpawnedProjectile = GetWorld()->SpawnActor<AEnemyProjectileActor>(EnemyProjectileType, AttackBeginPos, FRotator(0.f,0.f,0.f), SpawnParameters);
	SpawnedProjectile->SetTargetAndStartProjectile(ActorToAttack);
}
