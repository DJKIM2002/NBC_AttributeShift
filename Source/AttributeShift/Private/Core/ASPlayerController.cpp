#include "Core/ASPlayerController.h"

#include "Character/ASCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Manager/ASLogManager.h"
#include "Property/ASObjectPropertyActorComponent.h"
#include "GameFramework/Actor.h"
#include "Core/ASPlayerState.h"
#include "Property/ObjectPropertyData.h"

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
	AASPlayerState* ASPlayerState = GetASPlayerState();
	if (ASPlayerState == nullptr)
	{
		FASLogManager::Warning(TEXT("플레이어 상태를 찾을 수 없어 추출을 진행할 수 없습니다."));
		return;
	}

	// 이미 속성을 들고 있으면 새 속성을 추출 할 수 없음
	if (ASPlayerState->HasProperty())
	{
		FASLogManager::Warning(TEXT("이미 속성을 보유 중이므로 추출할 수 없습니다."));
		return;
	}

	// 현재 바라보는 대상의 속성 컴포넌트를 가져옴
	UASObjectPropertyActorComponent* PropertyComponent = GetTargetPropertyComponent();
	if (PropertyComponent == nullptr)
	{
		FASLogManager::Warning(TEXT("바라보는 대상에서 속성 컴포넌트를 찾을 수 없습니다."));
		return;
	}

	FASObjectPropertyData ExtractedPropertyData;

	// 대상에서 속성 추출을 시도
	if (!PropertyComponent->ExtractProperty(ExtractedPropertyData))
	{
		FASLogManager::Warning(TEXT("대상에서 속성 추출에 실패했습니다."));
		return;
	}

	// 추출한 속성을 플레이어가 획득할 수 있는지 확인
	if (!ASPlayerState->TryAcquireProperty(ExtractedPropertyData))
	{
		FASLogManager::Warning(TEXT("플레이어가 추출한 속성을 획득할 수 없습니다."));

		// To-Do: 속성 추출 후 획득 실패 시 원상 복구
		return;
	}

	FASLogManager::Log(TEXT("속성 추출에 성공했습니다!"));
	UpdateHUD();
}

void AASPlayerController::RequestInject()
{
	AASPlayerState* ASPlayerState = GetASPlayerState();
	if (ASPlayerState == nullptr)
	{
		FASLogManager::Warning(TEXT("플레이어 상태를 찾을 수 없어 주입을 진행할 수 없습니다."));
		return;
	}

	// 현재 플레이어가 들고 있는 속성이 없으면 주입 불가
	if (!ASPlayerState->HasProperty())
	{
		FASLogManager::Warning(TEXT("보유 중인 속성이 없어 주입할 수 없습니다."));
		return;
	}

	// 현재 바라보는 대상의 속성 컴포넌트를 가져옴
	UASObjectPropertyActorComponent* PropertyComponent = GetTargetPropertyComponent();
	if (PropertyComponent == nullptr)
	{
		FASLogManager::Warning(TEXT("바라보는 대상에서 속성 컴포넌트를 찾을 수 없습니다."));
		return;
	}

	// 현재 플레이어가 들고 있는 속성 데이터를 가져옴
	const FASObjectPropertyData CurrentPropertyData = ASPlayerState->GetCurrentPropertyData();

	// 대상 오브젝트에 속성 적용을 시도
	if (!PropertyComponent->ApplyProperty(CurrentPropertyData))
	{
		FASLogManager::Warning(TEXT("대상 오브젝트에 속성 주입에 실패했습니다."));
		return;
	}

	// 주입에 성공했으면 플레이어 속성을 비움
	if (!ASPlayerState->ClearProperty())
	{
		FASLogManager::Warning(TEXT("주입 후 플레이어 속성 초기화에 실패했습니다."));
		return;
	}

	FASLogManager::Log(TEXT("속성 주입에 성공했습니다!"));
	UpdateHUD();
}

void AASPlayerController::UpdateHUD()
{
	// To-Do: 추후 플레이어 보유 속성, 현재 상호작용 대상, 퍼즐 진행도 등을 반영
}

void AASPlayerController::HandlePlayerPropertyChanged(const FASObjectPropertyData& NewPropertyData)
{
	UpdateHUD();
}

AASCharacter* AASPlayerController::GetASCharacter() const
{
	return Cast<AASCharacter>(GetPawn());
}

AASPlayerState* AASPlayerController::GetASPlayerState() const
{
	return GetPlayerState<AASPlayerState>();
}

UASObjectPropertyActorComponent* AASPlayerController::GetTargetPropertyComponent() const
{
	AASCharacter* ASCharacter = GetASCharacter();
	if (ASCharacter == nullptr)
	{
		return nullptr;
	}

	AActor* TargetActor = ASCharacter->TraceInteractable();
	if (TargetActor == nullptr)
	{
		return nullptr;
	}

	return TargetActor->FindComponentByClass<UASObjectPropertyActorComponent>();
}
