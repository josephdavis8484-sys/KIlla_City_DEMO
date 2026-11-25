#include "UI/CopperCashHUD.h"

#include "Engine/Canvas.h"
#include "Interfaces/InteractableInterface.h"
#include "Player/EconomyComponent.h"
#include "Player/KillaCharacter.h"

void ACopperCashHUD::DrawHUD()
{
    Super::DrawHUD();
    const AKillaCharacter* Player = Cast<AKillaCharacter>(GetOwningPawn());
    if (!Canvas || !Player)
    {
        return;
    }

    const UEconomyComponent* Economy = Player->GetEconomy();
    const int32 Cash = Economy->GetDirtyCash();
    const int32 Loot = Economy->GetStolenLootValue();
    const float CenterX = Canvas->ClipX * 0.5f;
    const float CenterY = Canvas->ClipY * 0.5f;
    const FLinearColor Gold(1.0f, 0.76f, 0.30f);
    DrawRect(FLinearColor(0.025f, 0.035f, 0.045f, 0.92f), 18, 18, 388, 112);
    DrawText(TEXT("COPPER & CASH  /  JULIAN VANCE"), Gold, 30, 27, nullptr, 1.2f);
    DrawText(FString::Printf(TEXT("Dirty cash: $%d    Stolen goods: $%d"), Cash, Loot),
        FLinearColor::White, 30, 53, nullptr, 1.1f);

    const TCHAR* Objective = TEXT("Collect $100 in goods from the warehouse and house.");
    if (Cash >= 100)
    {
        Objective = TEXT("Copper & Cash complete. Lab capital secured.");
    }
    else if (Cash + static_cast<int64>(Loot) >= 100)
    {
        Objective = TEXT("Fence your goods at the pawn shop on the right.");
    }
    DrawText(Objective, FLinearColor::White, 30, 78);
    DrawText(TEXT("WASD  Move     Mouse  Look     Space  Jump     E  Interact"),
        FLinearColor::White, 30, 105);
    DrawRect(FLinearColor::White, CenterX - 2, CenterY - 2, 4, 4);

    const auto DrawCentered = [this, CenterX](const FString& Text, float Y, FLinearColor Color)
    {
        float Width = 0.0f;
        float Height = 0.0f;
        GetTextSize(Text, Width, Height);
        DrawRect(FLinearColor(0.025f, 0.035f, 0.045f, 0.9f),
            CenterX - Width / 2.0f - 9.0f, Y - 5.0f, Width + 18.0f, Height + 10.0f);
        DrawText(Text, Color, CenterX - Width / 2.0f, Y);
    };

    if (AActor* Target = Player->FindInteractable())
    {
        DrawCentered(TEXT("[E] ") + IInteractableInterface::Execute_GetInteractPrompt(Target).ToString(),
            CenterY + 22.0f, FLinearColor::White);
    }

    const FText Feedback = Player->GetFeedback();
    if (!Feedback.IsEmpty())
    {
        DrawCentered(Feedback.ToString(), CenterY + 58.0f, Gold);
    }
}
