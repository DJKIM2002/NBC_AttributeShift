#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Property/ObjectPropertyTypes.h"
#include "ASPlayerState.generated.h"

UCLASS()
class ATTRIBUTESHIFT_API AASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AASPlayerState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	bool bHasStoredProperty;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void StoreProperty(EObjectPropertyType InPropertyType);

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void ClearProperty();
};
