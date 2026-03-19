#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Property/ObjectPropertyTypes.h"
#include "ASObjectPropertyActorComponent.generated.h"

UCLASS(ClassGroup=(AttributeShift), meta=(BlueprintSpawnableComponent))
class ATTRIBUTESHIFT_API UASObjectPropertyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASObjectPropertyActorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Property")
	EObjectPropertyType CurrentPropertyType;

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	EObjectPropertyType ExtractProperty();

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void ApplyProperty(EObjectPropertyType InPropertyType);

	UFUNCTION(BlueprintCallable, Category = "Attribute Shift|Property")
	void RefreshVisualState();
};
