#include "Property/ASObjectPropertyActorComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Components/MeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

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

void UASObjectPropertyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateVisualByProperty();
	UpdatePhysicsByProperty();
}

void UASObjectPropertyActorComponent::UpdateVisualByProperty()
{
	// To-Do: 머티리얼, 색상, 파티클 등 속성별 연출을 이 함수에서 처리
	// Refactor 필요

	// 비주얼 갱신 대상 컴포넌트를 찾음
	UPrimitiveComponent* PrimitiveComponent = FindTargetPrimitiveComponent();
	if (PrimitiveComponent == nullptr)
	{
		return;
	}

	UMeshComponent* MeshComponent = Cast<UMeshComponent>(PrimitiveComponent);
	if (MeshComponent == nullptr)
	{
		return;
	}

	// 현재 속성 타입에 맞는 색상을 결정
	FLinearColor TargetColor = DefaultColor;

	switch (CurrentPropertyData.PropertyType)
	{
	case EObjectPropertyType::Fire:
		TargetColor = FireColor;
		break;

	case EObjectPropertyType::Ice:
		TargetColor = IceColor;
		break;

	case EObjectPropertyType::Electricity:
		TargetColor = ElectricityColor;
		break;

	case EObjectPropertyType::Wind:
		TargetColor = WindColor;
		break;

	default:
		break;
	}

	// 각 머티리얼 슬롯에 동적 머티리얼 인스턴스를 만들어 색상 파라미터를 반영
	const int32 MaterialCount = MeshComponent->GetNumMaterials();
	for (int32 MaterialIndex = 0; MaterialIndex < MaterialCount; ++MaterialIndex)
	{
		UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(MaterialIndex);
		if (DynamicMaterial == nullptr)
		{
			continue;
		}

		// 머티리얼에 미리 만들어 둔 ColorTint 파라미터를 갱신
		DynamicMaterial->SetVectorParameterValue(TEXT("ColorTint"), TargetColor);
	}
}

void UASObjectPropertyActorComponent::UpdatePhysicsByProperty()
{
	// To-Do: 질량, 마찰력, 탄성 등 속성별 물리값을 이 함수에서 처리
	// Refactor 필요

	// 물리 갱신 대상 컴포넌트를 찾음
	UPrimitiveComponent* PrimitiveComponent = FindTargetPrimitiveComponent();
	if (PrimitiveComponent == nullptr)
	{
		return;
	}

	// 물리 시뮬레이션이 꺼져 있으면 반영하지 않음
	if (!PrimitiveComponent->IsSimulatingPhysics())
	{
		return;
	}

	// 기본값으로 먼저 초기화
	float TargetMassScale = DefaultMassScale;
	float TargetLinearDamping = DefaultLinearDamping;

	switch (CurrentPropertyData.PropertyType)
	{
	case EObjectPropertyType::Weight:
		// 무게 속성 -> 질량 배율을 높임
		TargetMassScale = WeightMassScale;
		break;

	case EObjectPropertyType::Ice:
		// 얼음 속성 -> 감쇠를 낮춰 더 잘 미끄러지게 만듦
		TargetLinearDamping = IceLinearDamping;
		break;

	default:
		break;
	}

	// 현재 속성에 맞는 물리값을 적용
	PrimitiveComponent->SetMassScale(NAME_None, TargetMassScale);
	PrimitiveComponent->SetLinearDamping(TargetLinearDamping);
}

UPrimitiveComponent* UASObjectPropertyActorComponent::FindTargetPrimitiveComponent() const
{
	// 소유 액터가 없으면 적용 대상을 찾을 수 없음
	AActor* OwnerActor = GetOwner();
	if (OwnerActor == nullptr)
	{
		return nullptr;
	}

	// 소유 액터에서 첫 번째 PrimitiveComponent를 찾아 반환
	return OwnerActor->FindComponentByClass<UPrimitiveComponent>();
}
