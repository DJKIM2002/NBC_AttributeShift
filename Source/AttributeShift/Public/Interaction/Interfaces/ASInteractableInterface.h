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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attribute Shift|Interaction")
	bool CanInteract(APawn* Interactor) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attribute Shift|Interaction")
	void Interact(APawn* Interactor);
};
