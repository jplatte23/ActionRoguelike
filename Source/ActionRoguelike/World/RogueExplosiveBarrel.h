// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class UNiagaraSystem;
class URadialForceComponent;
class UStaticMeshComponent;
class UAudioComponent;
class UNiagaraComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	
	UPROPERTY(EditAnywhere, Category="Explosive Barrel")
	float ExplosionDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> BurningSound;
	
	FTimerHandle ExplosionTimeHandle;
	bool bHasExploded = false;
	
	void Explode();
	
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
