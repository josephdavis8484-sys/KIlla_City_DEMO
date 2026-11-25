#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EconomyComponent.generated.h"

UCLASS(ClassGroup=(KillaCity), meta=(BlueprintSpawnableComponent))
class KILLACITY_API UEconomyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Economy")
    bool AddStolenLoot(int32 Value);

    UFUNCTION(BlueprintCallable, Category="Economy")
    int32 FenceLoot();

    int32 GetDirtyCash() const { return DirtyCash; }
    int32 GetStolenLootValue() const { return StolenLootValue; }

private:
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    int32 DirtyCash = 0;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    int32 StolenLootValue = 0;
};
