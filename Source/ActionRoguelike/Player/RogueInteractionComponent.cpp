// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "ActionRoguelike/Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::Interact()
{
	IRogueInteractionInterface* InteractInterface = Cast<IRogueInteractionInterface>(SelectedActor);
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PlayerController = CastChecked<APlayerController>(this->GetOwner());
	FVector Center = PlayerController->GetPawn()->GetActorLocation();
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0f;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (OverlapLocation-Center).GetSafeNormal();
		
		float dotResult = FVector::DotProduct(OverlapDirection,  PlayerController->GetControlRotation().Vector());
		
		if (dotResult > HighestDotResult)
		{
			HighestDotResult = dotResult;
			BestActor = Overlap.GetActor();
		}
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		FString debugString = FString::Printf(TEXT("Dot: %f" ), dotResult);
		DrawDebugString(GetWorld(), OverlapLocation, debugString, nullptr, FColor::White, 0.0f, true); 
	}
	SelectedActor = BestActor;

	if (BestActor != nullptr)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
}

