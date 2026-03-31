#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ASUserWidget.generated.h"

class UTextBlock;

UCLASS()
class ATTRIBUTESHIFT_API UASUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 현재 플레이어 보유 속성 표시를 갱신
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|UI")
	void UpdatePropertyDisplay(const FText& PropertyNameText, bool bHasProperty);

protected:
	// 현재 보유 속성 이름을 표시하는 텍스트 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_CurrentProperty;
};
