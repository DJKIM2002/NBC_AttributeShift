#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Property/ObjectPropertyTypes.h"
#include "ASObjectPropertyActorComponent.generated.h"

UCLASS(ClassGroup=(AttributeShift), meta=(BlueprintSpawnableComponent))
class ATTRIBUTESHIFT_API UASObjectPropertyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASObjectPropertyActorComponent();

	// 현재 속성이 있는지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool HasProperty() const;

	// 현재 속성 타입 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	EObjectPropertyType GetCurrentPropertyType() const;

	// 현재 상태에서 추출 가능한지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool CanExtract() const;

	// 현재 상태에서 특정 속성을 주입 가능한지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool CanInject(EObjectPropertyType NewPropertyType) const;

	// 현재 속성을 추출하고 오브젝트 상태를 비움
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool TryExtractProperty(EObjectPropertyType& OutExtractedPropertyType);

	// 새 속성을 주입
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool TryInjectProperty(EObjectPropertyType NewPropertyType);

protected:
	// 현재 오브젝트가 보유한 속성
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;
};
