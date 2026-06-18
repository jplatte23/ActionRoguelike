#include "RogueBlackholeProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueBlackholeProjectile::ARogueBlackholeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ForceStrength = -800000.0f;
	RadialForceComponent->Radius = 1200.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	InitialLifeSpan = 5.0f;
}

void ARogueBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueBlackholeProjectile::OnSphereOverlappedComponent);
}


void ARogueBlackholeProjectile::OnSphereOverlappedComponent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}





