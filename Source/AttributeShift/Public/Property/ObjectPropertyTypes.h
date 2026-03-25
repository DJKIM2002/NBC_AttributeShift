#pragma once

#include "CoreMinimal.h"
#include "ObjectPropertyTypes.generated.h"

UENUM(BlueprintType)
enum class EObjectPropertyType : uint8
{
	// 속성이 없는 기본 상태
	None UMETA(DisplayName = "None"),

	// 무게 속성
	Weight UMETA(DisplayName = "Weight"),

	// 탄성 속성
	Elasticity UMETA(DisplayName = "Elasticity"),

	// 온도 속성
	Temperature UMETA(DisplayName = "Temperature"),

	// 불 속성
	Fire UMETA(DisplayName = "Fire"),

	// 얼음 속성
	Ice UMETA(DisplayName = "Ice"),

	// 바람 속성
	Wind UMETA(DisplayName = "Wind"),

	// 전기 속성
	Electricity UMETA(DisplayName = "Electricity")
};
