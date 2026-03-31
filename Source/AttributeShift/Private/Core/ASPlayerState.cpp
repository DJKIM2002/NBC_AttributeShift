#include "Core/ASPlayerState.h"
#include "UObject/EnumProperty.h"

AASPlayerState::AASPlayerState()
{
	// 시작 시 플레이어는 빈 속성 상태로 초기화
	CurrentPropertyData.Clear();
}

bool AASPlayerState::HasProperty() const
{
	// None이 아니면 현재 속성을 보유 중인 상태
	return CurrentPropertyData.IsValid();
}

const FASObjectPropertyData& AASPlayerState::GetCurrentPropertyData() const
{
	return CurrentPropertyData;
}

EObjectPropertyType AASPlayerState::GetCurrentPropertyType() const
{
	return CurrentPropertyData.PropertyType;
}

FText AASPlayerState::GetCurrentPropertyDisplayName() const
{
	return StaticEnum<EObjectPropertyType>()->GetDisplayNameTextByValue(
		static_cast<int64>(CurrentPropertyData.PropertyType));
}

bool AASPlayerState::SetCurrentProperty(const FASObjectPropertyData& InPropertyData)
{
	// 유효하지 않은 속성 데이터는 저장하지 않음
	if (!InPropertyData.IsValid())
	{
		return false;
	}

	// 현재 속성 데이터를 새 값으로 교체
	CurrentPropertyData = InPropertyData;

	// UI 등 외부 시스템에 상태 변경을 알림
	OnPlayerPropertyChanged.Broadcast(CurrentPropertyData);
	return true;
}

bool AASPlayerState::TryAcquireProperty(const FASObjectPropertyData& NewPropertyData)
{
	// 유효하지 않은 속성은 획득할 수 없음
	if (!NewPropertyData.IsValid())
	{
		return false;
	}

	// 이미 속성을 들고 있으면 새 속성을 획득할 수 없음
	if (HasProperty())
	{
		return false;
	}

	// 새 속성 데이터를 저장
	CurrentPropertyData = NewPropertyData;

	// UI 등 외부 시스템에 상태 변경을 알림
	OnPlayerPropertyChanged.Broadcast(CurrentPropertyData);
	return true;
}

bool AASPlayerState::ClearProperty()
{
	// 현재 속성이 없으면 비울 것이 없으므로 실패 처리
	if (!HasProperty())
	{
		return false;
	}

	// 속성 데이터를 빈 상태로 초기화
	CurrentPropertyData.Clear();

	// UI 등 외부 시스템에 상태 변경을 알림
	OnPlayerPropertyChanged.Broadcast(CurrentPropertyData);
	return true;
}
