#include "Player/KillaCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "Interfaces/InteractableInterface.h"
#include "Player/EconomyComponent.h"
#include "UObject/ConstructorHelpers.h"

AKillaCharacter::AKillaCharacter()
{
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = 480.0f;

    Economy = CreateDefaultSubobject<UEconomyComponent>(TEXT("Economy"));
    USpringArmComponent* Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    Arm->SetupAttachment(RootComponent);
    Arm->TargetArmLength = 320.0f;
    Arm->SocketOffset = FVector(0.0f, 55.0f, 45.0f);
    Arm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(Arm, USpringArmComponent::SocketName);

    UStaticMeshComponent* Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrototypeBody"));
    Body->SetupAttachment(RootComponent);
    Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Body->SetRelativeScale3D(FVector(0.55f, 0.43f, 1.5f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    Body->SetStaticMesh(Cylinder.Object);
}

void AKillaCharacter::PawnClientRestart()
{
    const APlayerController* PC = Cast<APlayerController>(GetController());
    auto* Input = PC
        ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())
        : nullptr;
    if (Input && Controls)
    {
        Input->RemoveMappingContext(Controls);
    }

    Super::PawnClientRestart();
    if (Input && Controls)
    {
        Input->AddMappingContext(Controls, 0);
    }
}

void AKillaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    Controls = NewObject<UInputMappingContext>(this);

    auto MakeAction = [this](EInputActionValueType Type)
    {
        UInputAction* Action = NewObject<UInputAction>(Controls);
        Action->ValueType = Type;
        return Action;
    };

    UInputAction* Forward = MakeAction(EInputActionValueType::Axis1D);
    UInputAction* Right = MakeAction(EInputActionValueType::Axis1D);
    UInputAction* Aim = MakeAction(EInputActionValueType::Axis2D);
    UInputAction* Use = MakeAction(EInputActionValueType::Boolean);
    UInputAction* JumpAction = MakeAction(EInputActionValueType::Boolean);

    Controls->MapKey(Forward, EKeys::W);
    Controls->MapKey(Forward, EKeys::S).Modifiers.Add(NewObject<UInputModifierNegate>(Controls));
    Controls->MapKey(Right, EKeys::D);
    Controls->MapKey(Right, EKeys::A).Modifiers.Add(NewObject<UInputModifierNegate>(Controls));
    Controls->MapKey(Aim, EKeys::Mouse2D);
    Controls->MapKey(Use, EKeys::E);
    Controls->MapKey(JumpAction, EKeys::SpaceBar);

    Input->BindAction(Forward, ETriggerEvent::Triggered, this, &AKillaCharacter::MoveForward);
    Input->BindAction(Right, ETriggerEvent::Triggered, this, &AKillaCharacter::MoveRight);
    Input->BindAction(Aim, ETriggerEvent::Triggered, this, &AKillaCharacter::Look);
    Input->BindAction(Use, ETriggerEvent::Started, this, &AKillaCharacter::Interact);
    Input->BindAction(JumpAction, ETriggerEvent::Started, static_cast<ACharacter*>(this), &ACharacter::Jump);
    Input->BindAction(JumpAction, ETriggerEvent::Completed, static_cast<ACharacter*>(this), &ACharacter::StopJumping);
}

void AKillaCharacter::MoveForward(const FInputActionValue& Value)
{
    const FRotator Heading(0.0, GetControlRotation().Yaw, 0.0);
    AddMovementInput(Heading.Vector(), Value.Get<float>());
}

void AKillaCharacter::MoveRight(const FInputActionValue& Value)
{
    const FRotator Heading(0.0, GetControlRotation().Yaw, 0.0);
    AddMovementInput(FRotationMatrix(Heading).GetUnitAxis(EAxis::Y), Value.Get<float>());
}

void AKillaCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D Mouse = Value.Get<FVector2D>();
    AddControllerYawInput(Mouse.X);
    AddControllerPitchInput(-Mouse.Y);
}

AActor* AKillaCharacter::FindInteractable() const
{
    const FVector Start = Camera->GetComponentLocation();
    const FVector End = Start + Camera->GetForwardVector() * 700.0;
    FCollisionQueryParams Query;
    Query.AddIgnoredActor(this);
    FHitResult Hit;
    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Query))
    {
        AActor* Candidate = Hit.GetActor();
        if (Candidate && Candidate->Implements<UInteractableInterface>() &&
            FVector::DistSquared(GetActorLocation(), Hit.ImpactPoint) <= FMath::Square(300.0))
        {
            FCollisionQueryParams ReachQuery = Query;
            ReachQuery.AddIgnoredActor(Candidate);
            if (!GetWorld()->LineTraceTestByChannel(GetPawnViewLocation(), Hit.ImpactPoint, ECC_Visibility, ReachQuery))
            {
                return Candidate;
            }
        }
    }

    return nullptr;
}

void AKillaCharacter::Interact()
{
    if (AActor* Target = FindInteractable())
    {
        IInteractableInterface::Execute_OnInteract(Target, this);
    }
}

void AKillaCharacter::ShowFeedback(const FText& Message)
{
    Feedback = Message;
    FeedbackUntil = GetWorld()->GetTimeSeconds() + 3.0f;
}

FText AKillaCharacter::GetFeedback() const
{
    return GetWorld()->GetTimeSeconds() < FeedbackUntil ? Feedback : FText::GetEmpty();
}
