#include "Core/ASGameMode.h"

#include "Character/ASCharacter.h"
#include "Core/ASGameState.h"
#include "Core/ASPlayerController.h"
#include "Core/ASPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ASHUDBase.h"

AASGameMode::AASGameMode()
	: NextStageName(NAME_None)
{
	DefaultPawnClass = AASCharacter::StaticClass();
	PlayerControllerClass = AASPlayerController::StaticClass();
	PlayerStateClass = AASPlayerState::StaticClass();
	GameStateClass = AASGameState::StaticClass();
	HUDClass = AASHUDBase::StaticClass();
}

bool AASGameMode::CheckStageClear() const
{
	const AASGameState* ASGameState = GetASGameState();
	return ASGameState != nullptr && ASGameState->IsPuzzleSolved();
}

void AASGameMode::HandleStageClear()
{
	// 퍼즐이 해결된 경우에만 다음 처리로 넘어감
	if (!CheckStageClear())
	{
		return;
	}

	// To-Do: 연출, 사운드, UI 표시가 필요하면 이 지점에 추가
	MoveToNextStage();
}

void AASGameMode::MoveToNextStage()
{
	// 다음 스테이지 이름이 설정된 경우에만 레벨을 전환
	if (NextStageName != NAME_None)
	{
		UGameplayStatics::OpenLevel(this, NextStageName);
	}
}

AASGameState* AASGameMode::GetASGameState() const
{
	return GetGameState<AASGameState>();
}
