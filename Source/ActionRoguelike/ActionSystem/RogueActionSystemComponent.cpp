#include "RogueActionSystemComponent.h"

#include "NiagaraShared.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	Attributes.Health += InValueChange;
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f"), Attributes.Health);
}
