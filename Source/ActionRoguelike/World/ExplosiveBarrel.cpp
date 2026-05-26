// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("Physics Actor");
	RootComponent = StaticMeshComponent;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	RadialForceComponent->ImpulseStrength = 150000.0f;
	RadialForceComponent->Radius = 750.0f;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
}

void AExplosiveBarrel::Explode()
{
	bHasExploded = true;
	
	NiagaraComponent->Deactivate();
	AudioComponent->Deactivate();
	
	RadialForceComponent->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}

float AExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (bHasExploded || GetWorldTimerManager().TimerExists(ExplosionTimeHandle))
	{
		return ActualDamage;
	}
	
	NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, StaticMeshComponent, NAME_None,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	AudioComponent = UGameplayStatics::SpawnSoundAttached(BurningSound, StaticMeshComponent);
	
	GetWorldTimerManager().SetTimer(ExplosionTimeHandle, this, &AExplosiveBarrel::Explode, ExplosionDelay);
	
	return ActualDamage;
}

