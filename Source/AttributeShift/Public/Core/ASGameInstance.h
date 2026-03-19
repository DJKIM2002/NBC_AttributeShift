#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ASGameInstance.generated.h"

UCLASS()
class ATTRIBUTESHIFT_API UASGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UASGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Profile")
	int32 UnlockedStageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Profile")
	int32 TotalScore;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Profile")
	void LoadProfile();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Profile")
	void SaveProfile();
};
