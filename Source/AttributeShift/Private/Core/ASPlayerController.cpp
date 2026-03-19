#include "Core/ASPlayerController.h"

#include "Character/ASCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AASPlayerController::AASPlayerController()
{
}

void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext != nullptr)
			{
				InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	UpdateHUD();
}

void AASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetupInput();
}

void AASPlayerController::SetupInput()
{
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	AASCharacter* ASCharacter = GetASCharacter();

	if (EnhancedInput == nullptr || ASCharacter == nullptr)
	{
		return;
	}

	if (MoveAction != nullptr)
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, ASCharacter, &AASCharacter::Move);
	}

	if (LookAction != nullptr)
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, ASCharacter, &AASCharacter::Look);
	}

	if (JumpAction != nullptr)
	{
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, ASCharacter, &AASCharacter::StartJump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, ASCharacter, &AASCharacter::StopJump);
	}

	if (InteractAction != nullptr)
	{
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, ASCharacter, &AASCharacter::TryInteract);
	}

	if (ExtractAction != nullptr)
	{
		EnhancedInput->BindAction(ExtractAction, ETriggerEvent::Started, this, &AASPlayerController::RequestExtract);
	}

	if (InjectAction != nullptr)
	{
		EnhancedInput->BindAction(InjectAction, ETriggerEvent::Started, this, &AASPlayerController::RequestInject);
	}
}

void AASPlayerController::RequestExtract()
{
	if (AASCharacter* ASCharacter = GetASCharacter())
	{
		ASCharacter->TryInteract();
	}
}

void AASPlayerController::RequestInject()
{
	if (AASCharacter* ASCharacter = GetASCharacter())
	{
		ASCharacter->TryInteract();
	}
}

void AASPlayerController::UpdateHUD()
{
}

AASCharacter* AASPlayerController::GetASCharacter() const
{
	return Cast<AASCharacter>(GetPawn());
}
