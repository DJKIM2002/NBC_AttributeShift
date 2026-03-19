#include "Character/ASCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "Interaction/Interfaces/ASInteractableInterface.h"

AASCharacter::AASCharacter()
	: InteractionTraceDistance(400.0f)
	, LookUpRate(1.0f)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.0f;
	GetCharacterMovement()->AirControl = 0.35f;
}

void AASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AASCharacter::TryInteract()
{
	if (AActor* TargetActor = TraceInteractable())
	{
		if (TargetActor->GetClass()->ImplementsInterface(UASInteractableInterface::StaticClass()))
		{
			if (IASInteractableInterface::Execute_CanInteract(TargetActor, this))
			{
				IASInteractableInterface::Execute_Interact(TargetActor, this);
			}
		}
	}
}

AActor* AASCharacter::TraceInteractable() const
{
	if (Controller == nullptr)
	{
		return nullptr;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FVector TraceEnd = ViewLocation + (ViewRotation.Vector() * InteractionTraceDistance);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ASCharacterTraceInteractable), false, this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility, QueryParams);
	return bHit ? HitResult.GetActor() : nullptr;
}

void AASCharacter::StartJump()
{
	Jump();
}

void AASCharacter::StopJump()
{
	StopJumping();
}

void AASCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	const FRotator ControlRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveValue.Y);
	AddMovementInput(RightDirection, MoveValue.X);
}

void AASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}
