// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnRailPawn.h"
#include "BulletActor.h"
#include "OnRailPawnPlayer.generated.h"

/**
 *
 */
UCLASS()
class PERSONALGAME_API AOnRailPawnPlayer : public AOnRailPawn
{
	GENERATED_BODY()
public:
	AOnRailPawnPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called when player is attacked 
	void Take_Damage();

	UFUNCTION(BlueprintCallable)
	int GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsReloading() const;

	UFUNCTION(BlueprintCallable)
	int GetAmmo() const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	class UCameraComponent * Camera;
	
	UPROPERTY(EditAnywhere, Category=Gun)
	class UStaticMeshComponent * GunMesh;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	//Attach to muzzle of GunMesh, Used to aim gun to position in screen space 
	UPROPERTY(EditAnywhere,Category=Gun)
	class USceneComponent * MuzzleStart;

	//Time it takes to reload 
	UPROPERTY(EditAnywhere, Category =Timer)
	float ReloadTime = 1.f;

	//Delay between the last time the player shot and when they can shoot again 
	UPROPERTY(EditAnywhere, Category =Timer)
	float DelayBetweenShots = 0.3f;

	UPROPERTY(EditAnywhere, Category=Gun)
	int MaxAmmo = 20;

	UPROPERTY(VisibleAnywhere, Category =State)
	int CurrentAmmo = 500;

	UPROPERTY(EditAnywhere)
	int MaxHealth = 5;

	UPROPERTY(VisibleAnywhere, Category = State)
	int CurrentHealth = 5;

	//Sets reloading state variables then calls timer function reload
	void Reload();

	//Sets shooting state variables then calls timer function Shoot 
	void Shoot();

	//Used to add delay between reload call and EndReload
	FTimerHandle ReloadTimerHandle;

	//Settable to AbulletActor or any of it's subclasses. Class that spawns on shoot
	UPROPERTY(EditAnywhere, Category=Gun)
	TSubclassOf<ABulletActor> BulletType;

	//Resets state variables allowing user to shoot and reload  again
	UFUNCTION()
	void EndReload();

	//Used to add delay between shoot call and EndShoot
	FTimerHandle ShootTimerHandle;

	//Reset state variables allowing user to shoot again
	UFUNCTION()
	void EndShoot();

	//State Variables. 
	UPROPERTY(VisibleAnywhere, Category=State)
	bool bIsReloading = false;
	UPROPERTY(VisibleAnywhere, Category=State)
	bool bHasAmmo = true;
	UPROPERTY(VisibleAnywhere, Category=State)
	bool bIsShooting = false;


	//Where the gun is aiming
	FVector CurrentAimPoint;

	//Converts mouse position to world space, then rotates gun to look at that position 
	void AimGun();

	void Die();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* PlayerHitSound;

};
