#include "Core/ASPlayerState.h"

AASPlayerState::AASPlayerState()
	: CurrentPropertyType(EObjectPropertyType::None)
{
}

void AASPlayerState::StoreProperty(const EObjectPropertyType InPropertyType)
{
	CurrentPropertyType = InPropertyType;
}

bool AASPlayerState::HasProperty() const
{
	return CurrentPropertyType != EObjectPropertyType::None;
}

EObjectPropertyType AASPlayerState::GetCurrentPropertyType() const
{
	return CurrentPropertyType;
}

bool AASPlayerState::TryAcquireProperty(EObjectPropertyType NewPropertyType)
{
	// None 속성은 획득 불가
	if (NewPropertyType == EObjectPropertyType::None)
	{
		return false;
	}

	// 이미 속성을 들고 있으면 새 속성을 받을 수 없음
	if (HasProperty())
	{
		return false;
	}

	CurrentPropertyType = NewPropertyType;
	return true;
}

bool AASPlayerState::ClearProperty()
{
	if (!HasProperty())
	{
		return false;
	}

	CurrentPropertyType = EObjectPropertyType::None;
	return true;
}
