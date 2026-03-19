#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class ATTRIBUTESHIFT_API AASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AASCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// 정면의 상호작용 대상에게 상호작용을 시도
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void TryInteract();

	// 전방 Line Trace로 상호작용 가능한 액터를 찾음
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	AActor* TraceInteractable() const;

	// 점프 시작 입력을 처리
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Movement")
	void StartJump();

	// 점프 종료 입력을 처리
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Movement")
	void StopJump();

	// 2D 이동 입력값을 받아 캐릭터를 이동
	void Move(const FInputActionValue& Value);

	// 2D 시점 입력값을 받아 카메라 방향을 회전
	void Look(const FInputActionValue& Value);

protected:
	// 상호작용 판정에 사용할 Trace 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	float InteractionTraceDistance;

	// 상하 시점 회전에 사용할 기본 배율
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Movement")
	float LookUpRate;
};
