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

	// 현재까지 해금된 스테이지 마지막 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Profile")
	int32 UnlockedStageIndex;

	// 스테이지를 넘기며 누적되는 총 점수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Shift|Profile")
	int32 TotalScore;

	// 저장된 프로필 데이터 불러오기
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Profile")
	void LoadProfile();

	// 현재 프로필 데이터를 저장
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Profile")
	void SaveProfile();
};
