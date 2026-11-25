#include "World/CopperCashActors.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Player/EconomyComponent.h"
#include "Player/KillaCharacter.h"
#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "CopperCashActors"

ACopperCashInteractable::ACopperCashInteractable()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    Mesh->SetStaticMesh(Cube.Object);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}

void ALootableActor::SetLoot(const FText& Name, int32 Value)
{
    LootName = Name;
    LootValue = Value;
}

FText ALootableActor::GetInteractPrompt_Implementation() const
{
    return FText::Format(LOCTEXT("Collect", "Take {0}"), LootName);
}

void ALootableActor::OnInteract_Implementation(AKillaCharacter* Player)
{
    if (bCollected || !Player || !Player->GetEconomy()->AddStolenLoot(LootValue))
    {
        return;
    }

    bCollected = true;
    Player->ShowFeedback(FText::Format(LOCTEXT("Collected", "Picked up {0}"), LootName));
    Destroy();
}

FText APawnShopActor::GetInteractPrompt_Implementation() const
{
    return LOCTEXT("Fence", "Fence all stolen goods");
}

void APawnShopActor::OnInteract_Implementation(AKillaCharacter* Player)
{
    if (!Player)
    {
        return;
    }

    UEconomyComponent* Economy = Player->GetEconomy();
    if (Economy->GetStolenLootValue() == 0)
    {
        Player->ShowFeedback(LOCTEXT("Empty", "Bring goods from the warehouse or house."));
        return;
    }

    const int32 Sale = Economy->FenceLoot();
    Player->ShowFeedback(Sale > 0
        ? FText::Format(LOCTEXT("Sold", "Fenced goods for ${0}"), FText::AsNumber(Sale))
        : LOCTEXT("SaleFailed", "This sale would exceed your cash limit."));
}

#undef LOCTEXT_NAMESPACE
