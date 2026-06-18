#include "RogueTeleportProjectile.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARogueTeleportProjectile::ARogueTeleportProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 6000.0f;
}

void ARogueTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::TeleportAfterDelay, DetonateDelay);
}

void ARogueTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void ARogueTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
										  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	
	TeleportAfterDelay();
}

void ARogueTeleportProjectile::TeleportAfterDelay()
{
	PlayExplosionEffects();
	ProjectileMovementComponent->StopMovementImmediately();
	// Hide all visuals and prevent any further collision while we wait on the teleport timer
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::HandleTeleport, TeleportSecondaryDelay);
}

void ARogueTeleportProjectile::HandleTeleport()
{
	APawn* ActorToTeleport = GetInstigator();
	check(ActorToTeleport);
	
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	
	Destroy();
}


