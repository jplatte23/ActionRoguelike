// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "Engine/OverlapResult.h"


URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PlayerController = CastChecked<APlayerController>(this->GetOwner());
	FVector Center = PlayerController->GetPawn()->GetActorLocation();
	
	//DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Red);
	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0f;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		FVector OverlapDirection = (OverlapLocation-Center).GetSafeNormal();
		
		float dotResult = FVector::DotProduct(OverlapDirection,  PlayerController->GetControlRotation().Vector());
		FString debugString = FString::Printf(TEXT("Dot: %f" ), dotResult);
		DrawDebugString(GetWorld(), OverlapLocation, debugString, nullptr, FColor::White, 0.0f, true); 
		
		if (dotResult > HighestDotResult)
		{
			HighestDotResult = dotResult;
			BestActor = Overlap.GetActor();
		}
	}
	if (BestActor != nullptr)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
	
}

