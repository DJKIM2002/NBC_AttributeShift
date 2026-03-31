#pragma once

#include "CoreMinimal.h"
#include "Core/ASPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Property/ObjectPropertyData.h"
#include "ASPlayerController.generated.h"

class AASCharacter;
class UInputAction;
class UInputMappingContext;
class ASObjectPropertyActorComponent;

UCLASS()
class ATTRIBUTESHIFT_API AASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AASPlayerController();

	virtual void BeginPlay() override;

	// InputComponent가 준비되면 실제 액션 바인딩을 수행
	virtual void SetupInputComponent() override;

	virtual void SetPawn(APawn* InPawn) override;

	// 액션과 함수 연결을 설정
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Input")
	void SetupInput();

	// Extract 입력이 들어왔을 때 호출
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void RequestExtract();

	// Inject 입력이 들어왔을 때 호출
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void RequestInject();

	// HUD 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|UI")
	void UpdateHUD();

protected:
	// 현재 소유 중인 캐릭터 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Input")
	AASCharacter* GetASCharacter() const;

	// 현재 플레이어 상태를 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Player")
	AASPlayerState* GetASPlayerState() const;

	// 현재 바라보는 액터의 속성 컴포넌트를 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Interaction")
	UASObjectPropertyActorComponent* GetTargetPropertyComponent() const;

	// 플레이어에게 기본으로 적용할 입력 매핑 컨텍스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// 이동 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> MoveAction;

	// 시점 회전 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> LookAction;

	// 점프 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> JumpAction;

	// 일반 상호작용 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> InteractAction;

	// 속성 추출 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> ExtractAction;

	// 속성 주입 입력용 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> InjectAction;

	// 플레이어 속성 변경 이벤트 처리
	UFUNCTION()
	void HandlePlayerPropertyChanged(const FASObjectPropertyData& NewPropertyData);

	// 플레이어 상태의 UI 갱신 이벤트 바인딩
	void BindPlayerStateEvents();
};
