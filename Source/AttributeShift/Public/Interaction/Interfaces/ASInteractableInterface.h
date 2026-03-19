#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASInteractableInterface.generated.h"

class APawn;

UINTERFACE(Blueprintable)
class ATTRIBUTESHIFT_API UASInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class ATTRIBUTESHIFT_API IASInteractableInterface
{
	GENERATED_BODY()

public:
	// 현재 상호작용이 가능한 상태인지 검사
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attribute Shift|Interaction")
	bool CanInteract(APawn* Interactor) const;

	// 실제 상호작용 동작을 수행
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attribute Shift|Interaction")
	void Interact(APawn* Interactor);
};
