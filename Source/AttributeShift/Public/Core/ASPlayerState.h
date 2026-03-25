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

	// 현재 플레이어가 들고 있는 속성
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;

	// 플레이어에게 새 속성을 저장
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void StoreProperty(EObjectPropertyType InPropertyType);

	// 플레이어가 속성을 들고 있는지 여부 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool HasProperty() const;
	
	// 현재 플레이어가 들고 있는 속성 가져오기
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	EObjectPropertyType GetCurrentPropertyType() const;
	
	// 속성을 새로 얻을 수 있는지 여부 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool TryAcquireProperty(EObjectPropertyType NewPropertyType);
	
	// 플레이어가 들고 있던 속성을 비움
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool ClearProperty();
};
