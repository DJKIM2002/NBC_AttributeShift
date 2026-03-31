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
	virtual void BeginPlay() override;
	
	// 현재 오브젝트가 보유 중인 속성 데이터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	FASObjectPropertyData CurrentPropertyData;

	// 속성 변경에 맞춰 비주얼을 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void UpdateVisualByProperty();

	// 속성 변경에 맞춰 물리 속성을 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void UpdatePhysicsByProperty();

	// 속성이 없을 때 사용할 기본 색상
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Visual")
	FLinearColor DefaultColor = FLinearColor::White;

	// '불' 속성일 때 사용할 색상
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Visual")
	FLinearColor FireColor = FLinearColor(1.0f, 0.2f, 0.0f, 1.0f);

	// '얼음' 속성일 때 사용할 색상
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Visual")
	FLinearColor IceColor = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);

	// '전기' 속성일 때 사용할 색상
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Visual")
	FLinearColor ElectricityColor = FLinearColor(1.0f, 1.0f, 0.2f, 1.0f);

	// '바람' 속성일 때 사용할 색상
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Visual")
	FLinearColor WindColor = FLinearColor(0.7f, 1.0f, 0.9f, 1.0f);

	// 기본 질량 배율
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Physics")
	float DefaultMassScale = 1.0f;

	// 기본 선형 감쇠값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Physics")
	float DefaultLinearDamping = 0.01f;

	// '무게' 속성 적용 시 질량 배율
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Physics")
	float WeightMassScale = 3.0f;

	// '얼음' 속성 적용 시 선형 감쇠값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Physics")
	float IceLinearDamping = 0.0f;

private:
	// 속성 적용 대상을 찾음
	UPrimitiveComponent* FindTargetPrimitiveComponent() const;
};
