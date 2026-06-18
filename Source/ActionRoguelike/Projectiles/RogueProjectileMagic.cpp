// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "Kismet/GameplayStatics.h"

ARogueProjectileMagic::ARogueProjectileMagic()
{
	
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	FVector HitFromDirection = GetActorRotation().Vector();

	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitFromDirection, Hit,  GetInstigatorController(),
		this, DmgTypeClass);
}

