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

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	bool CheckStageClear() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void HandleStageClear();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Stage")
	void MoveToNextStage();

protected:
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|Stage")
	AASGameState* GetASGameState() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Stage")
	FName NextStageName;
};
