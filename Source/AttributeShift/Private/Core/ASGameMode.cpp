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
	if (CheckStageClear())
	{
		MoveToNextStage();
	}
}

void AASGameMode::MoveToNextStage()
{
	if (NextStageName != NAME_None)
	{
		UGameplayStatics::OpenLevel(this, NextStageName);
	}
}

AASGameState* AASGameMode::GetASGameState() const
{
	return GetGameState<AASGameState>();
}
