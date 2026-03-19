#include "Property/ASObjectPropertyActorComponent.h"

UASObjectPropertyActorComponent::UASObjectPropertyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentPropertyType = EObjectPropertyType::None;
}

EObjectPropertyType UASObjectPropertyActorComponent::ExtractProperty()
{
	const EObjectPropertyType ExtractedProperty = CurrentPropertyType;
	CurrentPropertyType = EObjectPropertyType::None;
	RefreshVisualState();
	return ExtractedProperty;
}

void UASObjectPropertyActorComponent::ApplyProperty(const EObjectPropertyType InPropertyType)
{
	CurrentPropertyType = InPropertyType;
	RefreshVisualState();
}

void UASObjectPropertyActorComponent::RefreshVisualState()
{
}
