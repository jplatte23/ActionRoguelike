#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueBlackholeProjectile.generated.h"

class UNiagaraComponent;
class URadialForceComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueBlackholeProjectile : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UFUNCTION()
	void OnSphereOverlappedComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	ARogueBlackholeProjectile();

	virtual void PostInitializeComponents() override;

};
