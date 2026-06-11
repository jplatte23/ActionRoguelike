#include "RogueItemChest.h"

#include "Misc/MapErrors.h"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComponent"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::Interact()
{
	//Play Animation
	SetActorTickEnabled(true);
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentLidPitch = FMath::FInterpConstantTo(CurrentLidPitch, AnimationTargetPitch, DeltaTime, AnimationSpeed);
	
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentLidPitch, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(CurrentLidPitch, AnimationTargetPitch))
	{
		SetActorTickEnabled(false);
	}
}

