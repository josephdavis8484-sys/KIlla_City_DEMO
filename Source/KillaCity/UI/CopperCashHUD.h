#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CopperCashHUD.generated.h"

UCLASS()
class KILLACITY_API ACopperCashHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
