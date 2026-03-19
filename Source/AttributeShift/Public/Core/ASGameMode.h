#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ASGameMode.generated.h"

class AASGameState;

UCLASS()
class ATTRIBUTESHIFT_API AASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AASGameMode();

	// 현재 레벨이 클리어 가능한 상태인지 검사
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	bool CheckStageClear() const;

	// 스테이지 클리어 처리
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void HandleStageClear();

	// 다음 스테이지로 이동
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void MoveToNextStage();

protected:
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Stage")
	AASGameState* GetASGameState() const;

	// 다음에 열 스테이지 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Stage")
	FName NextStageName;
};
