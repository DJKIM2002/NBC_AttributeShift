#include "UI/Widgets/ASUserWidget.h"

#include "Components/TextBlock.h"

void UASUserWidget::UpdatePropertyDisplay(const FText& PropertyNameText, bool bHasProperty)
{
	// 텍스트 위젯이 연결되지 않았으면 갱신하지 않음
	if (Text_CurrentProperty == nullptr)
	{
		return;
	}

	// 현재 속성이 없으면 기본 문구를 표시
	if (!bHasProperty)
	{
		Text_CurrentProperty->SetText(FText::FromString("속성 없음"));
		return;
	}

	// 현재 속성 이름을 화면에 표시
	Text_CurrentProperty->SetText(PropertyNameText);
}
