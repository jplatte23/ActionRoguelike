#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueTeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueTeleportProjectile : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	FTimerHandle TeleportHandle;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DetonateDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float TeleportSecondaryDelay = 0.2f;
	
	void TeleportAfterDelay();
	void HandleTeleport();
	
	virtual void BeginPlay() override;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
public:
	ARogueTeleportProjectile();
	
	virtual void PostInitializeComponents() override;
};
