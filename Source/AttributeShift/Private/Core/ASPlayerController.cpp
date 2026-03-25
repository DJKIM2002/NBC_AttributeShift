#include "Core/ASPlayerController.h"

#include "Character/ASCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Manager/ASLogManager.h"

AASPlayerController::AASPlayerController()
{
	bReplicates = false;
}

void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>())
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

void AASPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Pawn이 실제로 연결되는 시점에 다시 입력 바인딩 시도
	if (InputComponent != nullptr)
	{
		SetupInput();
	}
}

void AASPlayerController::SetupInput()
{
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	AASCharacter* ASCharacter = GetASCharacter();

	if (EnhancedInput == nullptr)
	{
		FASLogManager::Warning(TEXT("EnhancedInputComponent가 없어 입력 바인딩을 진행할 수 없습니다."));
		return;
	}

	if (ASCharacter == nullptr)
	{
		FASLogManager::Warning(TEXT("현재 소유한 캐릭터가 없어 입력 바인딩을 건너뜁니다."));
		return;
	}

	// Pawn 재소유 시 중복 바인딩을 막기 위해 기존 액션 바인딩 정리
	EnhancedInput->ClearActionBindings();

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

	if (ExtractAction != nullptr)
	{
		EnhancedInput->BindAction(ExtractAction, ETriggerEvent::Started, this, &AASPlayerController::RequestExtract);
	}

	if (InjectAction != nullptr)
	{
		EnhancedInput->BindAction(InjectAction, ETriggerEvent::Started, this, &AASPlayerController::RequestInject);
	}

	if (InteractAction != nullptr)
	{
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, ASCharacter, &AASCharacter::TryInteract);
	}
}

void AASPlayerController::RequestExtract()
{
	FASLogManager::Log(TEXT("Extract interaction requested."));
}

void AASPlayerController::RequestInject()
{
	FASLogManager::Log(TEXT("Inject interaction requested."));
}

void AASPlayerController::UpdateHUD()
{
}

AASCharacter* AASPlayerController::GetASCharacter() const
{
	return Cast<AASCharacter>(GetPawn());
}

AASPlayerState* AASPlayerController::GetASPlayerState() const
{
	return GetPlayerState<AASPlayerState>();
}
