// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	float AnimationSpeed = 50.0f;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	float AnimationTargetPitch = 120.0f;
	
	float CurrentLidPitch = 0.0f;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	ARogueItemChest();
};
