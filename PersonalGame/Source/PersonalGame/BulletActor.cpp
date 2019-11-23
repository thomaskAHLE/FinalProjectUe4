// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/SphereComponent.h"
#include "ShootableInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"

// Sets default values
ABulletActor::ABulletActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletCollision = CreateDefaultSubobject<USphereComponent>("BulletCollision");
	SetRootComponent(BulletCollision);
	BulletCollision->InitSphereRadius(BulletRadius);
	BulletCollision->SetGenerateOverlapEvents(true);
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnOverlapBegin);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->UpdatedComponent = BulletCollision;
	ProjectileMovement->InitialSpeed = BulletInitSpeed;
	ProjectileMovement->MaxSpeed = BulletMaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = false;

	this->InitialLifeSpan = LifeSpan;
}

void ABulletActor::DestroyWrapper()
{
	Destroy();
}

void ABulletActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped %s"), *OtherActor->GetName())
		//Don't want to destroy the bullet if it is overlapping itself, or if it is overlapping the player who shot it. 
		if (OtherActor == this || OtherActor == GetOwner())
		{
			return;
		}
		else
		{
			
			if (OtherActor->GetClass()->ImplementsInterface(UShootableInterface::StaticClass()))
			{
				IShootableInterface::Execute_OnShot(OtherActor, BulletDamage);
				GetWorld()->GetTimerManager().SetTimer(DelayBeforeDestroyTimerHandle, this, &ABulletActor::DestroyWrapper, DelayBeforeDestroy, false);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("not shootable"))
			}
		}
	}
	
}

