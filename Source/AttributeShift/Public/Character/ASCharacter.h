#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ATTRIBUTESHIFT_API AASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AASCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// 플레이어가 상호작용 키를 눌렀을 때 호출
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void TryInteract();

	// 전방 트레이스를 통해 상호작용 가능한 액터를 찾음
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	AActor* TraceInteractable();
	
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	bool CanInteractWithActor(AActor* TargetActor);

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
	// 캐릭터 뒤에서 따라오는 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	// 실제 플레이어 시점 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	// 카메라와 캐릭터 사이 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Camera")
	float TargetArmLength;
	
	// 상호작용 트레이스 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	float InteractionTraceDistance;

	// 상하 시점 민감도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Movement")
	float LookUpRate;
};
