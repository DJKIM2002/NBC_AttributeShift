#pragma once

#include "CoreMinimal.h"
#include "Property/ObjectPropertyTypes.h"
#include "ObjectPropertyData.generated.h"

USTRUCT(BlueprintType)
struct ATTRIBUTESHIFT_API FASObjectPropertyData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType = EObjectPropertyType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	bool bCanExtract = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Property")
	bool bCanInject = true;
};
