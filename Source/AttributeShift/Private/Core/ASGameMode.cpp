#include "Core/ASGameMode.h"

#include "Core/ASGameState.h"
#include "Kismet/GameplayStatics.h"

AASGameMode::AASGameMode()
	: NextStageName(NAME_None)
{
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
