#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ASGameState.generated.h"

UCLASS()
class ATTRIBUTESHIFT_API AASGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AASGameState();

	// 현재 활성화된 스위치 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 ActivatedSwitchCount;

	// 퍼즐 해결에 필요한 전체 스위치 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 RequiredSwitchCount;

	// 퍼즐 진행 상황을 한 번에 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void UpdatePuzzleProgress(int32 InActivatedSwitchCount, int32 InRequiredSwitchCount);

	// 퍼즐이 해결되었는지 여부를 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Puzzle")
	bool IsPuzzleSolved() const;
};
