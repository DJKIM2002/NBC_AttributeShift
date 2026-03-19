#pragma once

#include "CoreMinimal.h"
#include "Property/ObjectPropertyTypes.h"
#include "ObjectPropertyData.generated.h"

USTRUCT(BlueprintType)
struct ATTRIBUTESHIFT_API FASObjectPropertyData
{
	GENERATED_BODY()

	// 오브젝트가 현재 보유한 속성 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType = EObjectPropertyType::None;

	// 이 오브젝트에서 속성을 추출할 수 있는지 여부 검사
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	bool bCanExtract = true;

	// 이 오브젝트에 속성을 주입할 수 있는지 여부 검사
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	bool bCanInject = true;
};
