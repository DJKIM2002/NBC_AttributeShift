#pragma once

#include "CoreMinimal.h"
#include "ASInteractTraceTypes.generated.h"

class AActor;
class UPrimitiveComponent;

USTRUCT(BlueprintType)
struct ATTRIBUTESHIFT_API FASInteractTraceResult
{
	GENERATED_BODY()

	// Trace에 맞은 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	TObjectPtr<AActor> HitActor = nullptr;

	// Trace에 맞은 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	TObjectPtr<UPrimitiveComponent> HitComponent = nullptr;

	// 충돌 지점 월드 좌표
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	FVector ImpactPoint = FVector::ZeroVector;

	// 실제로 막히는 충돌이 있었는지 여부 검사
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	bool bBlockingHit = false;
};
