// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class UAudioComponent;
class USoundBase;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileMagic : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass; 
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
public:
	virtual void PostInitializeComponents() override;
	ARogueProjectileMagic();

};
