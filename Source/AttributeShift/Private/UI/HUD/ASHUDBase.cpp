#include "UI/HUD/ASHUDBase.h"

#include "UI/Widgets/ASUserWidget.h"

void AASHUDBase::BeginPlay()
{
	Super::BeginPlay();

	// HUD 위젯 클래스가 설정되지 않았으면 생성하지 않음
	if (MainUserWidgetClass == nullptr)
	{
		return;
	}

	// 메인 HUD 위젯 생성
	MainUserWidget = CreateWidget<UASUserWidget>(GetWorld(), MainUserWidgetClass);
	if (MainUserWidget == nullptr)
	{
		return;
	}

	// 생성된 위젯을 화면에 추가
	MainUserWidget->AddToViewport();
}

UASUserWidget* AASHUDBase::GetMainUserWidget() const
{
	return MainUserWidget;
}

void AASHUDBase::UpdatePropertyDisplay(const FText& PropertyNameText, bool bHasProperty)
{
	// 메인 HUD 위젯이 없으면 갱신하지 않음
	if (MainUserWidget == nullptr)
	{
		return;
	}
	
	// 실제 표시 로직은 UserWidget이 담당
	MainUserWidget->UpdatePropertyDisplay(PropertyNameText, bHasProperty);
}
