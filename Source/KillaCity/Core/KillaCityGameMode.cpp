#include "Core/KillaCityGameMode.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Player/KillaCharacter.h"
#include "UI/CopperCashHUD.h"
#include "Engine/StaticMesh.h"
#include "World/CopperCashActors.h"

AKillaCityGameMode::AKillaCityGameMode()
{
    DefaultPawnClass = AKillaCharacter::StaticClass();
    HUDClass = ACopperCashHUD::StaticClass();
}

void AKillaCityGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    // Entry is the prototype's empty map. Authored maps can place their own actors.
    if (!MapName.EndsWith(TEXT("Entry")))
    {
        return;
    }

    UWorld* World = GetWorld();
    FActorSpawnParameters Spawn;
    Spawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    const auto Block = [World, &Spawn](UStaticMesh* Mesh, const FVector& Location, const FVector& Scale)
    {
        AStaticMeshActor* Actor = World->SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator, Spawn);
        UStaticMeshComponent* Component = Actor->GetStaticMeshComponent();
        Component->SetMobility(EComponentMobility::Movable);
        Component->SetStaticMesh(Mesh);
        Component->SetCollisionProfileName(TEXT("BlockAll"));
        Actor->SetActorScale3D(Scale);
    };

    UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    Block(Cube, FVector(550, 0, -20), FVector(28, 23, 0.4));

    const auto Room = [&Block, Cube](double X, double Y)
    {
        Block(Cube, FVector(X + 240, Y, 115), FVector(0.2, 4.8, 2.3));
        Block(Cube, FVector(X, Y - 230, 115), FVector(4.8, 0.2, 2.3));
        Block(Cube, FVector(X, Y + 230, 115), FVector(4.8, 0.2, 2.3));
        Block(Cube, FVector(X - 230, Y - 158, 115), FVector(0.2, 1.4, 2.3));
        Block(Cube, FVector(X - 230, Y + 158, 115), FVector(0.2, 1.4, 2.3));
    };

    Room(630, -570);
    Room(1030, 0);
    Room(630, 570);

    const auto Sign = [World, &Spawn](const TCHAR* Name, const FVector& Location)
    {
        AActor* Actor = World->SpawnActor<AActor>(Location, FRotator(0, 180, 0), Spawn);
        UTextRenderComponent* Text = NewObject<UTextRenderComponent>(Actor);
        Actor->SetRootComponent(Text);
        Text->SetWorldLocationAndRotation(Location, FRotator(0, 180, 0));
        Text->SetHorizontalAlignment(EHTA_Center);
        Text->SetWorldSize(30.0f);
        Text->SetText(FText::FromString(Name));
        Text->RegisterComponent();
    };
    Sign(TEXT("WAREHOUSE"), FVector(382, -570, 230));
    Sign(TEXT("WALDO HOUSE"), FVector(782, 0, 230));
    Sign(TEXT("PAWN SHOP"), FVector(382, 570, 230));

    const auto Loot = [World, &Spawn](const TCHAR* Name, int32 Value, const FVector& Location, const FVector& Scale)
    {
        ALootableActor* Actor = World->SpawnActor<ALootableActor>(Location, FRotator::ZeroRotator, Spawn);
        Actor->SetLoot(FText::FromString(Name), Value);
        Actor->SetActorScale3D(Scale);
    };
    Loot(TEXT("copper pipe"), 60, FVector(695, -570, 65), FVector(0.65, 1.1, 1.3));
    Loot(TEXT("jewelry box"), 40, FVector(1110, 0, 60), FVector(0.65, 0.8, 1.2));

    APawnShopActor* Counter = World->SpawnActor<APawnShopActor>(
        FVector(710, 570, 62), FRotator::ZeroRotator, Spawn);
    Counter->SetActorScale3D(FVector(0.75, 2.5, 1.24));

    World->SpawnActor<APlayerStart>(FVector(0, 0, 102), FRotator::ZeroRotator, Spawn);

    const auto AddDirectionalLight = [World, &Spawn](const FRotator& Rotation, float Intensity, bool bShadows)
    {
        ADirectionalLight* Light = World->SpawnActor<ADirectionalLight>(FVector::ZeroVector, Rotation, Spawn);
        UDirectionalLightComponent* Component = CastChecked<UDirectionalLightComponent>(Light->GetLightComponent());
        Component->SetMobility(EComponentMobility::Movable);
        Component->SetIntensity(Intensity);
        Component->SetCastShadows(bShadows);
        Component->SetForwardShadingPriority(bShadows ? 1 : 0);
    };
    AddDirectionalLight(FRotator(-48, -32, 0), 5.0f, true);
    AddDirectionalLight(FRotator(-24, 15, 0), 1.8f, false);
    AddDirectionalLight(FRotator(-30, 145, 0), 1.0f, false);

    ASkyLight* Sky = World->SpawnActor<ASkyLight>(FVector::ZeroVector, FRotator::ZeroRotator, Spawn);
    Sky->GetLightComponent()->SetMobility(EComponentMobility::Movable);
    Sky->GetLightComponent()->SetIntensity(0.8f);
}
