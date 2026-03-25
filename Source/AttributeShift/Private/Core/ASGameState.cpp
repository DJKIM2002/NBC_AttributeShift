#include "Core/ASGameState.h"

AASGameState::AASGameState()
	: RequiredSolvedCount(0)
	  , CurrentSolvedCount(0)
{
}

bool AASGameState::IsPuzzleSolved() const
{
	// 목표 수치가 0 이하이면 아직 유효한 퍼즐 목표가 없는 상태로 봄
	if (RequiredSolvedCount <= 0)
	{
		return false;
	}

	// 현재 진행도가 목표 이상이면 퍼즐이 해결된 상태
	return CurrentSolvedCount >= RequiredSolvedCount;
}

void AASGameState::SetRequiredSolvedCount(int32 NewRequiredSolvedCount)
{
	RequiredSolvedCount = NewRequiredSolvedCount;
}

void AASGameState::SetCurrentSolvedCount(int32 NewCurrentSolvedCount)
{
	CurrentSolvedCount = NewCurrentSolvedCount;
}

void AASGameState::AddSolvedCount(int32 Delta)
{
	// 음수 증가는 허용하지 않음
	if (Delta <= 0)
	{
		return;
	}

	CurrentSolvedCount += Delta;
}

void AASGameState::RemoveSolvedCount(int32 Delta)
{
	// 음수 감소는 허용하지 않음
	if (Delta <= 0)
	{
		return;
	}

	CurrentSolvedCount = FMath::Max(0, CurrentSolvedCount - Delta);
}

int32 AASGameState::GetRequiredSolvedCount() const
{
	return RequiredSolvedCount;
}

int32 AASGameState::GetCurrentSolvedCount() const
{
	return CurrentSolvedCount;
}
