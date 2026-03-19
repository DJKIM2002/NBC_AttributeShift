#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Property/ObjectPropertyTypes.h"
#include "ASPlayerState.generated.h"

UCLASS()
class ATTRIBUTESHIFT_API AASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AASPlayerState();

	// 플레이어가 현재 보관 중인 속성 타입
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;

	// 플레이어가 속성을 보유 중인지 검사
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	bool bHasStoredProperty;

	// 플레이어에게 새 속성을 저장
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void StoreProperty(EObjectPropertyType InPropertyType);

	// 플레이어가 들고 있던 속성을 비움
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void ClearProperty();
};
