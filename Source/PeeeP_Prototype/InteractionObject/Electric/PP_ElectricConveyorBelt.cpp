#include "InteractionObject/Electric/PP_ElectricConveyorBelt.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InterpToMovementComponent.h"

// Sets default values
APP_ElectricConveyorBelt::APP_ElectricConveyorBelt()
{
    PrimaryActorTick.bCanEverTick = true;

    // Mesh �� TriggerBox ����
    BeltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BP_Conveyor"));
    RootComponent = BeltMesh;
    BeltMesh->SetCollisionProfileName(TEXT("ElectricObjectProfile"));

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APP_ElectricConveyorBelt::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APP_ElectricConveyorBelt::OnOverlapEnd);

    // �⺻ �Ӽ� �ʱ�ȭ
    BeltSpeed = 300.0f;
    bIsActivated = false;
    BeltLength = 1000.0f;
    Tolerance = 10.0f;
    bIsCharged = false; // �ʱ⿡�� �������� ����

    // InterpToMovementComponent �ʱ�ȭ
    InterpToMovement = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpToMovementComponent"));
    InterpToMovement->bSweep = false;
}

void APP_ElectricConveyorBelt::BeginPlay()
{
    Super::BeginPlay();

    // InterpToMovement�� ����� �����Ǿ����� Ȯ��
    if (!InterpToMovement)
    {
        UE_LOG(LogTemp, Error, TEXT("InterpToMovement is not initialized properly!"));
        return;
    }
}

void APP_ElectricConveyorBelt::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsActivated)
    {
        TArray<AActor*> OverlappingActorsCopy = OverlappingActors;

        for (AActor* OverlappingActor : OverlappingActorsCopy)
        {
            if (OverlappingActor && !HasReachedEndOfBelt(OverlappingActor))
            {
                FVector NewLocation = OverlappingActor->GetActorLocation();
                FVector Velocity = GetActorForwardVector() * BeltSpeed;
                NewLocation += Velocity * DeltaTime;
                OverlappingActor->SetActorLocation(NewLocation);

                ActorVelocities.Add(OverlappingActor, Velocity);
            }
        }
    }
}

void APP_ElectricConveyorBelt::Charge()
{
    if (bIsCharged)	// �̹� ������ ���¶�� �ߺ����� ó������ ����
    {
        UE_LOG(LogTemp, Log, TEXT("This Platform is already Charged!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Platform Charged!"));
    bIsCharged = true;

    // ������ ����
    ReverseDirection();
}

void APP_ElectricConveyorBelt::ReverseDirection()
{
    // ��Ʈ�� �̵� �ӵ��� ������ ����
    BeltSpeed = -BeltSpeed;
}

// �浹 �߻� �� ó��
void APP_ElectricConveyorBelt::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        OverlappingActors.Add(OtherActor);
        bIsActivated = true;
    }
}

// �浹 ���� �� ó��
void APP_ElectricConveyorBelt::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        if (ActorVelocities.Contains(OtherActor))
        {
            FVector LastVelocity = ActorVelocities[OtherActor];

            if (ACharacter* Character = Cast<ACharacter>(OtherActor))
            {
                if (Character->GetCharacterMovement())
                {
                    Character->GetCharacterMovement()->Velocity.X = LastVelocity.X;
                    Character->GetCharacterMovement()->Velocity.Y = LastVelocity.Y;
                }
            }
            else if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent()))
            {
                PrimitiveComponent->AddImpulse(LastVelocity, NAME_None, true);
            }

            ActorVelocities.Remove(OtherActor);
        }

        OverlappingActors.Remove(OtherActor);
        if (OverlappingActors.Num() == 0)
        {
            bIsActivated = false;
        }
    }
}

// ��Ʈ ���� �����ߴ��� Ȯ��
bool APP_ElectricConveyorBelt::HasReachedEndOfBelt(AActor* Actor) const
{
    FVector BeltEndLocation = GetActorLocation() + GetActorForwardVector() * BeltLength;
    return FVector::Dist(Actor->GetActorLocation(), BeltEndLocation) < Tolerance;
}
