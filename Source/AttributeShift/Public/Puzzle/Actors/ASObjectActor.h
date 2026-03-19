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

	// 상호작용 가능 여부를 판단
	virtual bool CanInteract_Implementation(APawn* Interactor) const override;

	// 실제 상호작용 로직
	virtual void Interact_Implementation(APawn* Interactor) override;

protected:
	// 액터 루트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Components")
	TObjectPtr<USceneComponent> Root;

	// 오브젝트 속성을 저장/관리하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute Shift|Components")
	TObjectPtr<UASObjectPropertyActorComponent> ObjectPropertyComponent;
};
