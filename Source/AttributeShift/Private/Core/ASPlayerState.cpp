#include "Core/ASPlayerState.h"

AASPlayerState::AASPlayerState()
	: CurrentPropertyType(EObjectPropertyType::None)
	, bHasStoredProperty(false)
{
}

void AASPlayerState::StoreProperty(const EObjectPropertyType InPropertyType)
{
	CurrentPropertyType = InPropertyType;
	bHasStoredProperty = InPropertyType != EObjectPropertyType::None;
}

void AASPlayerState::ClearProperty()
{
	CurrentPropertyType = EObjectPropertyType::None;
	bHasStoredProperty = false;
}
