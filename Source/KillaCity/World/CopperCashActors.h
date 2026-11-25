#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "CopperCashActors.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract)
class KILLACITY_API ACopperCashInteractable : public AActor, public IInteractableInterface
{
    GENERATED_BODY()

public:
    ACopperCashInteractable();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
    TObjectPtr<UStaticMeshComponent> Mesh;
};

UCLASS()
class KILLACITY_API ALootableActor : public ACopperCashInteractable
{
    GENERATED_BODY()

public:
    void SetLoot(const FText& Name, int32 Value);
    virtual FText GetInteractPrompt_Implementation() const override;
    virtual void OnInteract_Implementation(AKillaCharacter* Player) override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loot", meta=(AllowPrivateAccess="true"))
    FText LootName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loot", meta=(AllowPrivateAccess="true", ClampMin="1"))
    int32 LootValue = 1;

    bool bCollected = false;
};

UCLASS()
class KILLACITY_API APawnShopActor : public ACopperCashInteractable
{
    GENERATED_BODY()

public:
    virtual FText GetInteractPrompt_Implementation() const override;
    virtual void OnInteract_Implementation(AKillaCharacter* Player) override;
};
