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

	// 오브젝트가 현재 가지고 있는 속성 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;

	// 현재 속성을 꺼내고, 내부 상태를 비움
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	EObjectPropertyType ExtractProperty();

	// 외부에서 전달된 속성을 오브젝트에 적용
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void ApplyProperty(EObjectPropertyType InPropertyType);

	// 속성 변경에 맞춰 비주얼을 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void RefreshVisualState();
};
