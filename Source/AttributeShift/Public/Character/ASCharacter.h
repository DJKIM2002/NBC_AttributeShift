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

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	void TryInteract();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Interaction")
	AActor* TraceInteractable() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Movement")
	void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Movement")
	void StopJump();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Interaction")
	float InteractionTraceDistance;
};
