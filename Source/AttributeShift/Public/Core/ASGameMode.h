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

	// 스테이지 클리어 여부를 확인
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	bool CheckStageClear() const;

	// 스테이지 클리어 시 후속 처리를 수행
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void HandleStageClear();

	// 다음 스테이지로 이동
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void MoveToNextStage();

protected:
	// 현재 게임 상태를 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Stage")
	AASGameState* GetASGameState() const;

	// 다음 스테이지 맵 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Stage")
	FName NextStageName;
};
