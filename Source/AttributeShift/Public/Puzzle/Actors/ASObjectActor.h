#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interfaces/ASInteractableInterface.h"
#include "ASObjectActor.generated.h"

class UASObjectPropertyActorComponent;
class USceneComponent;

UCLASS()
class ATTRIBUTESHIFT_API AASObjectActor : public AActor, public IASInteractableInterface
{
	GENERATED_BODY()

public:
	AASObjectActor();

	virtual bool CanInteract_Implementation(APawn* Interactor) const override;
	virtual void Interact_Implementation(APawn* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Components")
	TObjectPtr<UASObjectPropertyActorComponent> ObjectPropertyComponent;
};
