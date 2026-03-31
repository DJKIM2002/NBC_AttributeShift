#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Property/ObjectPropertyData.h"
#include "ASPlayerState.generated.h"

// 플레이어 보유 속성이 바뀌었을 때 알리는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPropertyChanged, const FASObjectPropertyData&, NewPropertyData);

UCLASS()
class ATTRIBUTESHIFT_API AASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AASPlayerState();

	// 플레이어가 현재 속성을 들고 있는지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool HasProperty() const;

	// 현재 플레이어가 들고 있는 속성 데이터 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	const FASObjectPropertyData& GetCurrentPropertyData() const;
	
	// UI에서 표시할 현재 속성 타입 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	EObjectPropertyType GetCurrentPropertyType() const;
	
	// UI에서 표시할 현재 속성 이름 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	FText GetCurrentPropertyDisplayName() const;

	// 플레이어에게 새 속성 데이터를 저장
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool SetCurrentProperty(const FASObjectPropertyData& InPropertyData);
	
	// 플레이어가 새 속성을 획득 시도
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool TryAcquireProperty(const FASObjectPropertyData& NewPropertyData);

	// 플레이어가 들고 있던 속성을 비움
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	bool ClearProperty();

	// 플레이어 보유 속성이 바뀌었을 때 알림
	UPROPERTY(BlueprintAssignable, Category = "Attribute Shift|Property")
	FOnPlayerPropertyChanged OnPlayerPropertyChanged;

protected:
	// 현재 플레이어가 보유 중인 속성 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	FASObjectPropertyData CurrentPropertyData;
};
