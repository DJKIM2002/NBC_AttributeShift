#pragma once

#include "CoreMinimal.h"
#include "ASInteractTraceTypes.generated.h"

class AActor;
class UPrimitiveComponent;

USTRUCT(BlueprintType)
struct ATTRIBUTESHIFT_API FASInteractTraceResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	TObjectPtr<AActor> HitActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	TObjectPtr<UPrimitiveComponent> HitComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	FVector ImpactPoint = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	bool bBlockingHit = false;
};
