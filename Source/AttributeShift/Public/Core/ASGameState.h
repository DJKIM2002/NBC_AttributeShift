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

	// 현재 퍼즐이 모두 해결되었는지 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	bool IsPuzzleSolved() const;

	// 퍼즐 목표 수치를 설정
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void SetRequiredSolvedCount(int32 NewRequiredSolvedCount);

	// 현재 해결된 퍼즐 수치를 설정
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void SetCurrentSolvedCount(int32 NewCurrentSolvedCount);

	// 현재 해결된 퍼즐 수치를 1 증가
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void AddSolvedCount(int32 Delta = 1);

	// 현재 해결된 퍼즐 수치를 1 감소
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	void RemoveSolvedCount(int32 Delta = 1);

	// 퍼즐 목표 수치를 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	int32 GetRequiredSolvedCount() const;

	// 현재 해결된 퍼즐 수치를 반환
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Puzzle")
	int32 GetCurrentSolvedCount() const;

protected:
	// 퍼즐 클리어에 필요한 목표 수치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 RequiredSolvedCount;

	// 현재 해결된 퍼즐 진행도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Puzzle")
	int32 CurrentSolvedCount;
};
