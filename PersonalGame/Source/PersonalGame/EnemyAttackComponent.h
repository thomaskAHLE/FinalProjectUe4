// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"


UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONALGAME_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void Attack(class AActor* ActorToAttack, float DamageToDeal, FVector AttackBeginPos);
};
