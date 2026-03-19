#include "Puzzle/Actors/ASObjectActor.h"

#include "Components/SceneComponent.h"
#include "Property/ASObjectPropertyActorComponent.h"

AASObjectActor::AASObjectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ObjectPropertyComponent = CreateDefaultSubobject<UASObjectPropertyActorComponent>(TEXT("ObjectPropertyComponent"));
}

bool AASObjectActor::CanInteract_Implementation(APawn* Interactor) const
{
	return Interactor != nullptr;
}

void AASObjectActor::Interact_Implementation(APawn* Interactor)
{
}
