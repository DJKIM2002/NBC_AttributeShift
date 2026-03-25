#pragma once

#include "CoreMinimal.h"
#include "Property/ObjectPropertyTypes.h"
#include "ObjectPropertyData.generated.h"

USTRUCT(BlueprintType)
struct ATTRIBUTESHIFT_API FASObjectPropertyData
{
	GENERATED_BODY()

	// 현재 속성 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	EObjectPropertyType PropertyType = EObjectPropertyType::None;

	// 속성 강도 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	float Strength = 0.0f;

	// 속성 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	float Duration = 0.0f;

	// 현재 유효한 속성인지 확인
	bool IsValid() const
	{
		return PropertyType != EObjectPropertyType::None;
	}

	// 빈 속성 데이터로 초기화
	void Clear()
	{
		PropertyType = EObjectPropertyType::None;
		Strength = 0.0f;
		Duration = 0.0f;
	}
};
