#include "Core/ASGameState.h"

AASGameState::AASGameState()
	: ActivatedSwitchCount(0)
	, RequiredSwitchCount(0)
{
}

void AASGameState::UpdatePuzzleProgress(const int32 InActivatedSwitchCount, const int32 InRequiredSwitchCount)
{
	ActivatedSwitchCount = InActivatedSwitchCount;
	RequiredSwitchCount = InRequiredSwitchCount;
}

bool AASGameState::IsPuzzleSolved() const
{
	return RequiredSwitchCount > 0 && ActivatedSwitchCount >= RequiredSwitchCount;
}
