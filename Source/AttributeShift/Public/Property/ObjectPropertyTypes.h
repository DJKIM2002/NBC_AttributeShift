#pragma once

#include "CoreMinimal.h"
#include "ObjectPropertyTypes.generated.h"

UENUM(BlueprintType)
enum class EObjectPropertyType : uint8
{
	None UMETA(DisplayName = "None"),
	AttributeA UMETA(DisplayName = "Attribute A"),
	AttributeB UMETA(DisplayName = "Attribute B"),
	AttributeC UMETA(DisplayName = "Attribute C")
};
