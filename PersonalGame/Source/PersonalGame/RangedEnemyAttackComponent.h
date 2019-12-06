// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackComponent.h"
#include "RangedEnemyAttackComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PERSONALGAME_API URangedEnemyAttackComponent : public UEnemyAttackComponent
{
	GENERATED_BODY()
public:
	virtual void Attack(class AActor* ActorToAttack, float DamageToDeal, FVector AttackBeginPos) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyProjectileActor> EnemyProjectileType;
};
