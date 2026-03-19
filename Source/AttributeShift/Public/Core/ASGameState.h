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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 ActivatedSwitchCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 RequiredSwitchCount;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void UpdatePuzzleProgress(int32 InActivatedSwitchCount, int32 InRequiredSwitchCount);

	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Puzzle")
	bool IsPuzzleSolved() const;
};
