#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KillaCharacter.generated.h"

class UEconomyComponent;
class UCameraComponent;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class KILLACITY_API AKillaCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AKillaCharacter();
    virtual void PawnClientRestart() override;
    UEconomyComponent* GetEconomy() const { return Economy; }
    AActor* FindInteractable() const;
    void ShowFeedback(const FText& Message);
    FText GetFeedback() const;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Interact();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    TObjectPtr<UEconomyComponent> Economy;

    UPROPERTY()
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY()
    TObjectPtr<UInputMappingContext> Controls;

    FText Feedback;
    float FeedbackUntil = 0.0f;
};
