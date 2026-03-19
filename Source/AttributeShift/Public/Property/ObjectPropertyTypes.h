#pragma once

#include "CoreMinimal.h"
#include "ObjectPropertyTypes.generated.h"

UENUM(BlueprintType)
enum class EObjectPropertyType : uint8
{
	// 속성이 비어 있는 상태
	None UMETA(DisplayName = "None"),

	// 수정 필요
	// 예시 속성 A
	AttributeA UMETA(DisplayName = "Attribute A"),

	// 예시 속성 B
	AttributeB UMETA(DisplayName = "Attribute B"),

	// 예시 속성 C
	AttributeC UMETA(DisplayName = "Attribute C")
};
