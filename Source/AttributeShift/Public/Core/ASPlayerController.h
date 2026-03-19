#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

class AASCharacter;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class ATTRIBUTESHIFT_API AASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AASPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Input")
	void SetupInput();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void RequestExtract();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void RequestInject();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|UI")
	void UpdateHUD();

protected:
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Input")
	AASCharacter* GetASCharacter() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> ExtractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|Input")
	TObjectPtr<UInputAction> InjectAction;
};
