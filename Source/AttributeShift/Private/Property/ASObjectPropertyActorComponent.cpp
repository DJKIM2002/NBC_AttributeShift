#include "Property/ASObjectPropertyActorComponent.h"

UASObjectPropertyActorComponent::UASObjectPropertyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentPropertyType = EObjectPropertyType::None;
}

bool UASObjectPropertyActorComponent::HasProperty() const
{
	return CurrentPropertyType != EObjectPropertyType::None;
}

EObjectPropertyType UASObjectPropertyActorComponent::GetCurrentPropertyType() const
{
	return CurrentPropertyType;
}

bool UASObjectPropertyActorComponent::CanExtract() const
{
	return HasProperty();
}

bool UASObjectPropertyActorComponent::CanInject(EObjectPropertyType NewPropertyType) const
{
	// None은 주입 불가
	if (NewPropertyType == EObjectPropertyType::None)
	{
		return false;
	}

	// 이미 속성이 있으면 주입 불가
	if (HasProperty())
	{
		return false;
	}

	return true;
}

bool UASObjectPropertyActorComponent::TryExtractProperty(EObjectPropertyType& OutExtractedPropertyType)
{
	if (!CanExtract())
	{
		return false;
	}

	OutExtractedPropertyType = CurrentPropertyType;
	CurrentPropertyType = EObjectPropertyType::None;
	return true;
}

bool UASObjectPropertyActorComponent::TryInjectProperty(EObjectPropertyType NewPropertyType)
{
	if (!CanInject(NewPropertyType))
	{
		return false;
	}

	CurrentPropertyType = NewPropertyType;
	return true;
}
