#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KillaCityGameMode.generated.h"

UCLASS()
class KILLACITY_API AKillaCityGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AKillaCityGameMode();
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
