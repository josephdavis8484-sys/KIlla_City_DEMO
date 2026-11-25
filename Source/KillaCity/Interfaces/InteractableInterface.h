#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

class AKillaCharacter;

UINTERFACE(BlueprintType)
class KILLACITY_API UInteractableInterface : public UInterface
{
    GENERATED_BODY()
};

class KILLACITY_API IInteractableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    FText GetInteractPrompt() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void OnInteract(AKillaCharacter* Player);
};
