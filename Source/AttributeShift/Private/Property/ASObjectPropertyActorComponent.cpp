#include "Property/ASObjectPropertyActorComponent.h"

UASObjectPropertyActorComponent::UASObjectPropertyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// 시작 시 오브젝트는 빈 속성 상태로 초기화
	CurrentPropertyData.Clear();
}

bool UASObjectPropertyActorComponent::HasProperty() const
{
	// None이 아니면 현재 속성을 보유 중인 상태
	return CurrentPropertyData.IsValid();
}

const FASObjectPropertyData& UASObjectPropertyActorComponent::GetCurrentPropertyData() const
{
	return CurrentPropertyData;
}


bool UASObjectPropertyActorComponent::CanExtract() const
{
	// 현재 속성이 있어야 추출 가능
	return HasProperty();
}

bool UASObjectPropertyActorComponent::CanApplyProperty(const FASObjectPropertyData& InPropertyData) const
{
	// 유효하지 않은 속성 데이터는 적용할 수 없음
	if (!InPropertyData.IsValid())
	{
		return false;
	}

	// 현재 이미 속성이 있으면 새 속성을 바로 적용하지 않음
	if (HasProperty())
	{
		return false;
	}

	return true;
}

bool UASObjectPropertyActorComponent::ExtractProperty(FASObjectPropertyData& OutPropertyData)
{
	// 추출 가능한 상태가 아니면 실패 처리
	if (!CanExtract())
	{
		return false;
	}

	// 현재 속성 데이터를 출력값으로 전달
	OutPropertyData = CurrentPropertyData;

	// 추출 후 오브젝트는 빈 속성 상태가 됨
	CurrentPropertyData.Clear();

	// 속성 변화에 맞게 비주얼과 물리를 갱신
	UpdateVisualByProperty();
	UpdatePhysicsByProperty();

	return true;
}

bool UASObjectPropertyActorComponent::ApplyProperty(const FASObjectPropertyData& InPropertyData)
{
	// 현재 상태에서 적용 가능하지 않으면 실패 처리
	if (!CanApplyProperty(InPropertyData))
	{
		return false;
	}

	// 새 속성 데이터를 저장
	CurrentPropertyData = InPropertyData;

	// 속성 변화에 맞게 비주얼과 물리를 갱신
	UpdateVisualByProperty();
	UpdatePhysicsByProperty();

	return true;
}

void UASObjectPropertyActorComponent::UpdateVisualByProperty()
{
	// To-Do: 머티리얼, 색상, 파티클 등 속성별 연출을 이 함수에서 처리
}

void UASObjectPropertyActorComponent::UpdatePhysicsByProperty()
{
	// To-Do: 질량, 마찰력, 탄성 등 속성별 물리값을 이 함수에서 처리
}
