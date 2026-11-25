#include "Player/EconomyComponent.h"

bool UEconomyComponent::AddStolenLoot(int32 Value)
{
    if (Value <= 0 || Value > MAX_int32 - StolenLootValue)
    {
        return false;
    }

    StolenLootValue += Value;
    return true;
}

int32 UEconomyComponent::FenceLoot()
{
    if (StolenLootValue > MAX_int32 - DirtyCash)
    {
        return 0;
    }

    const int32 Sale = StolenLootValue;
    DirtyCash += Sale;
    StolenLootValue = 0;
    return Sale;
}
