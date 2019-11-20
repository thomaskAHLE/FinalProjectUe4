// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailPawnPlayer.h"

#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "BulletActor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

AOnRailPawnPlayer::AOnRailPawnPlayer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>("GunMesh");
	GunMesh->SetupAttachment(RootComponent);

	MuzzleStart = CreateDefaultSubobject<USceneComponent>("MuzzleStart");
	MuzzleStart->SetupAttachment(GunMesh);

}

void AOnRailPawnPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AOnRailPawnPlayer::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AOnRailPawnPlayer::Reload);
}

void AOnRailPawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimGun();
}

void AOnRailPawnPlayer::Take_Damage()
{
	UE_LOG(LogTemp, Warning, TEXT("Taking damage"))
	--CurrentHealth;
	if (CurrentHealth <= 0)
	{
		Die();
	}
}

int AOnRailPawnPlayer::GetHealth() const
{
	return CurrentHealth;
}

bool AOnRailPawnPlayer::GetIsReloading() const
{
	return bIsReloading;
}

int AOnRailPawnPlayer::GetAmmo() const
{
	return CurrentAmmo;
}

void AOnRailPawnPlayer::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	 CurrentAmmo = MaxAmmo;
}

void AOnRailPawnPlayer::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reload Called"));
	if (!bIsReloading && !bIsShooting)
	{
		bIsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AOnRailPawnPlayer::EndReload, ReloadTime, false);

		if (ReloadSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
	    }
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Reload"));
	}
}

void AOnRailPawnPlayer::Shoot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Shoot Called"));
	if (!bIsShooting && !bIsReloading && bHasAmmo)
	{
		bIsShooting = true;
		--CurrentAmmo;
		//Not sure if correct collision channel
		FActorSpawnParameters BulletSpawnParams;
		BulletSpawnParams.Owner = this;

		BulletSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		GetWorld()->SpawnActor<ABulletActor>(BulletType, MuzzleStart->GetComponentLocation() , GunMesh->GetComponentRotation(), BulletSpawnParams);
		
		//called after DelayeBetweenShots seconds 
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AOnRailPawnPlayer::EndShoot, DelayBetweenShots, false);

		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't shoot yet"));
	}
}

void AOnRailPawnPlayer::EndReload()
{
	CurrentAmmo = MaxAmmo;
	bIsReloading = false;
	bHasAmmo = true;
	UE_LOG(LogTemp, Warning, TEXT("Reload Finished"));
}

void AOnRailPawnPlayer::EndShoot()
{
	bHasAmmo = 0 < CurrentAmmo;
	bIsShooting = false;
	if (!bHasAmmo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Shoot finished"));
}
/*Fix Me!*/
void AOnRailPawnPlayer::AimGun()
{
	FVector MouseWorldDirection;
	FVector MouseWordLocation;
	UWorld const * World = GetWorld();
	if (World != nullptr && World->GetFirstPlayerController() != nullptr)
	{
		APlayerController * PC = World->GetFirstPlayerController();
		float ScreenX, ScreenY;
		if (PC->GetMousePosition(/*out*/ ScreenX, /*out*/ ScreenY))
		{
			FVector2D ScreenPos{ ScreenX, ScreenY };
			ULocalPlayer * LocalPlayer = World->GetFirstLocalPlayerFromController();
			if (LocalPlayer != nullptr)
			{
				FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
					LocalPlayer->ViewportClient->Viewport,
					World->Scene,
					LocalPlayer->ViewportClient->EngineShowFlags)
					.SetRealtimeUpdate(true));
				FVector OutViewLocation;
				FRotator OutViewRotation;
				FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, OutViewLocation, OutViewRotation, LocalPlayer->ViewportClient->Viewport);
				if (SceneView != NULL)
				{
					FVector WorldOrigin, WorldDirection;
					SceneView->DeprojectFVector2D(ScreenPos, /*out*/ WorldOrigin, /*out*/ WorldDirection);
						
					FVector LookAtPos = 10000 * WorldDirection + MuzzleStart->GetComponentLocation();
					FCollisionQueryParams CollisionParams;
					CollisionParams.AddIgnoredActor(this);
					FHitResult HitResult;
					World->LineTraceSingleByChannel(HitResult, MuzzleStart->GetComponentLocation(), LookAtPos, ECollisionChannel::ECC_WorldStatic, CollisionParams);
					if (HitResult.bBlockingHit)
					{
						LookAtPos = HitResult.Location;
					}
					//DrawDebugLine(World, MuzzleStart->GetComponentLocation(), LookAtPos, FColor::Red);
					FRotator GunRotation = UKismetMathLibrary::FindLookAtRotation(GunMesh->GetComponentLocation(), LookAtPos);
					GunMesh->SetWorldRotation(GunRotation);
					CurrentAimPoint = (100 * WorldDirection) + MuzzleStart->GetComponentLocation();
				}
			}
		}
	}
}

void AOnRailPawnPlayer::Die()
{
	//Handle death and reload level 
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

	UE_LOG(LogTemp, Error, TEXT("%s died"), *GetName())
}
