#include "RogueActionSystemComponent.h"

#include "NiagaraShared.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	float MaxHealth = GetDefault<URogueActionSystemComponent>()->Attributes.Health;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyZero(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, MaxHealth: %f"), Attributes.Health, MaxHealth);
}
