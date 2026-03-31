#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ASHUDBase.generated.h"

class UASUserWidget;

UCLASS()
class ATTRIBUTESHIFT_API AASHUDBase : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// 현재 생성된 메인 HUD 위젯을 반환
	UFUNCTION(BlueprintPure, Category = "Attribute Shift|UI")
	UASUserWidget* GetMainUserWidget() const;

	// 플레이어 속성 표시 갱신 요청을 메인 위젯에 전달
	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|UI")
	void UpdatePropertyDisplay(const FText& PropertyNameText, bool bHasProperty);

protected:
	// 화면에 표시할 메인 HUD 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Shift|UI")
	TSubclassOf<UASUserWidget> MainUserWidgetClass;

	// 실제 생성된 메인 HUD 위젯 인스턴스
	TObjectPtr<UASUserWidget> MainUserWidget;
};
