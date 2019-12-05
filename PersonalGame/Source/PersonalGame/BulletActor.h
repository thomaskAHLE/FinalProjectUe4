// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitShootableSignature);

UCLASS()
class PERSONALGAME_API ABulletActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletActor();
	FHitShootableSignature OnHitShootable;
	void SetBulletMultiplier(const float BulletDamageMultiplier);
protected:
	UPROPERTY(EditAnywhere)
	class USphereComponent* BulletCollision;

	class UProjectileMovementComponent * ProjectileMovement;

	//Radius of sphere collider on bullet
	UPROPERTY(EditAnywhere)
	float BulletRadius = 10.f;

	UPROPERTY(EditAnywhere)
	float BulletInitSpeed =3000.f;

	UPROPERTY(EditAnywhere)
	float BulletMaxSpeed = 3000.f;

	//How long the bulletActor should live for before being destroyed, if it isn't destroyed by an overlap event 
	UPROPERTY(EditAnywhere)
    float LifeSpan = 3.f;	

	UPROPERTY(EditAnywhere)
		float BulletDamage = 1.f;

	FTimerHandle DelayBeforeDestroyTimerHandle;

	//The Time between BulletActor overlapping another object in the scene and when it should destroy itself
	UPROPERTY(EditAnywhere, Category=Timer)
	float DelayBeforeDestroy = .1f;
	
	//After overlap happens, sets a timer that calls this, after DelayBeforeDestroy seconds, which calls AActor::Destroy
	UFUNCTION()
	void DestroyWrapper();

public:

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
