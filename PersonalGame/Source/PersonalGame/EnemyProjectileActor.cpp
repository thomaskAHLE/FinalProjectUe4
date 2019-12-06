// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectileActor.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyProjectileActor::AEnemyProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArcSpline = CreateDefaultSubobject<USplineComponent>("ArcSpline");
	this->SetRootComponent(ArcSpline);
	ProjectileSphere = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	ProjectileSphere->SetupAttachment(RootComponent);
	ProjectileSphere->SetGenerateOverlapEvents(true);
	ProjectileFX = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileFX");
	ProjectileFX->SetupAttachment(ProjectileSphere);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyProjectileActor::OnProjectileOverlap);
	
	

}

void AEnemyProjectileActor::OnShot_Implementation(float Damage, FVector HitLocation, const TArray<FName> &ComponentTags)
{
	ProjectileSphere->SetGenerateOverlapEvents(false);
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentDistanceAlongSpline = 0.f;
	bMoveProjectileAlongSpline = false;
	ArcSpline->AddSplinePointAtIndex(GetActorLocation(), 0, ESplineCoordinateSpace::World);
	
}

void AEnemyProjectileActor::MoveAlongSpline(float DeltaDistance)
{
	CurrentDistanceAlongSpline += DeltaDistance;
	ProjectileSphere->SetWorldLocation(ArcSpline->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World));
}

// Called every frame
void AEnemyProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMoveProjectileAlongSpline)
	{
		MoveAlongSpline(DeltaTime * SpeedMultiplier);
	}
}

void AEnemyProjectileActor::SetTargetAndStartProjectile(AActor * Target)
{
	TargetActor = Target;
	ArcSpline->AddSplineWorldPoint(Target->GetActorLocation());
	float SplineLength = ArcSpline->GetSplineLength();
	FVector MiddleSplinePointLocation = ArcSpline->GetLocationAtDistanceAlongSpline(SplineLength / 2.f, ESplineCoordinateSpace::World);
	MiddleSplinePointLocation.Z += AdditionalHeightAboveSplineAtMidPoint;
	ArcSpline->AddSplinePoint(MiddleSplinePointLocation, ESplineCoordinateSpace::World);
	ArcSpline->SetLocationAtSplinePoint(1, MiddleSplinePointLocation, ESplineCoordinateSpace::World);
	ArcSpline->SetLocationAtSplinePoint(2, Target->GetActorLocation(), ESplineCoordinateSpace::World);
	bMoveProjectileAlongSpline = true;
}

void AEnemyProjectileActor::OnProjectileOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Overlapping %s"), *OtherActor->GetName());
		if (OtherActor == TargetActor)
		{
			DamageToDeal = 1;
			FDamageEvent DamageEvent;
			TargetActor->TakeDamage(DamageToDeal, DamageEvent, GetInstigatorController(), this);
			Destroy();
		}
	}
}

