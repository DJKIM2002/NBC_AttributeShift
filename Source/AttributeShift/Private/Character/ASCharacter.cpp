#include "Character/ASCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "Interaction/Interfaces/ASInteractableInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

AASCharacter::AASCharacter()
	: InteractionTraceDistance(400.0f)
	  , LookUpRate(1.0f)
	  , TargetArmLength(350.0f)
{
	// 컨트롤러의 Pitch/Roll/Yaw를 직접 쓰지 않고,
	// 카메라와 이동 설정으로 회전하도록 구성
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 이동 방향 기준으로 캐릭터가 회전하도록 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.0f;
	GetCharacterMovement()->AirControl = 0.35f;

	// 스프링 암 생성
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = TargetArmLength;
	// 컨트롤러 회전에 따라 카메라 암 회전
	CameraBoom->bUsePawnControlRotation = true;

	// 카메라 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 카메라는 암을 따라가고 자체 회전은 하지 않음
	FollowCamera->bUsePawnControlRotation = false;
}

void AASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AASCharacter::TryInteract()
{
	AActor* TargetActor = TraceInteractable();

	// 상호작용 가능한 대상이 아니면 아무 것도 하지 않음
	if (!CanInteractWithActor(TargetActor))
	{
		return;
	}

	// 이터페이스를 통해 대상 액터에 상호작용 요청
	IASInteractableInterface::Execute_Interact(TargetActor, this);
}

AActor* AASCharacter::TraceInteractable()
{
	// 컨트롤러가 없으면 시점을 알 수 없으므로 실패 처리
	if (Controller == nullptr)
	{
		return nullptr;
	}

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	// 카메라가 바라보는 정면 방향으로 트레이스 끝점 게산
	const FVector TraceEnd = ViewLocation + (ViewRotation.Vector() * InteractionTraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewLocation,
		TraceEnd,
		ECC_Visibility,
		QueryParams
	);

	DrawDebugLine(GetWorld(), ViewLocation, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.5f);

	if (!bHit)
	{
		return nullptr;
	}

	return HitResult.GetActor();
}

bool AASCharacter::CanInteractWithActor(AActor* TargetActor)
{
	// 대상이 없으면 상호작용 불가
	if (TargetActor == nullptr)
	{
		return false;
	}

	// 인터페이스를 구현하지 않았으면 상호작용 불가
	if (!TargetActor->GetClass()->ImplementsInterface(UASInteractableInterface::StaticClass()))
	{
		return false;
	}

	// 인터페이스가 있으면 실제 상호작용 가능 여부를 다시 확인
	return IASInteractableInterface::Execute_CanInteract(TargetActor, this);
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
