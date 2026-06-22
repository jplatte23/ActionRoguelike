// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectiles/RogueProjectileMagic.h"
#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"

class URogueActionSystemComponent;
class ARogueBlackholeProjectile;
class ARogueProjectile;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class UNiagaraSystem;
class ARogueProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;

UCLASS()
class ACTIONROGUELIKE_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoguePlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ARogueProjectile> PrimaryAttackProjectileClass;
	UPROPERTY(VisibleAnywhere, Category="PrimaryAttack")
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(EditDefaultsOnly, Category="SecondaryAttack")
	TSubclassOf<ARogueProjectile> SecondaryAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="SpecialAttack")
	TSubclassOf<ARogueProjectile> SpecialAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	UPROPERTY(EditDefaultsOnly, Category="Input")
   	TObjectPtr<UInputAction> Input_Jump;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& FDamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void Jump();
	UFUNCTION()
	void StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass);
	void AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
