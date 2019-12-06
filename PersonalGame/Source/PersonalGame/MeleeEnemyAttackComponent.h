// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackComponent.h"
#include "MeleeEnemyAttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class PERSONALGAME_API UMeleeEnemyAttackComponent : public UEnemyAttackComponent
{
	GENERATED_BODY()

public:
	virtual void Attack(class AActor* ActorToAttack, float DamageToDeal, FVector AttackBeginPos) override;
};
