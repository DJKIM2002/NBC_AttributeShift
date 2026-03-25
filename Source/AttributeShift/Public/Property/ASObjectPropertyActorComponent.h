#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Property/ObjectPropertyData.h"
#include "ASObjectPropertyActorComponent.generated.h"

UCLASS(ClassGroup=(AttributeShift), meta=(BlueprintSpawnableComponent))
class ATTRIBUTESHIFT_API UASObjectPropertyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASObjectPropertyActorComponent();

	// 현재 속성을 보유하고 있는지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool HasProperty() const;

	// 현재 속성 데이터 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	const FASObjectPropertyData& GetCurrentPropertyData() const;

	// 현재 상태에서 추출 가능한지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool CanExtract() const;

	// 현재 상태에서 속성 적용이 가능한지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool CanApplyProperty(const FASObjectPropertyData& InPropertyData) const;

	// 현재 속성을 추출하고 빈 상태로 만듦
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool ExtractProperty(FASObjectPropertyData& OutPropertyData);

	// 새 속성을 오브젝트에 적용
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool ApplyProperty(const FASObjectPropertyData& InPropertyData);

protected:
	// 현재 오브젝트가 보유 중인 속성 데이터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	FASObjectPropertyData CurrentPropertyData;

	// 속성 변경에 맞춰 비주얼을 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void UpdateVisualByProperty();

	// 속성 변경에 맞춰 물리 속성을 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void UpdatePhysicsByProperty();
};
