// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObject/Electric/PPGear_Test.h"
#include "Character/PPCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APPGear_Test::APPGear_Test()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽� ������Ʈ ����
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(false);								// ���� ������ ���� �ʴ´ٸ� �ݵ�� false�� ����.
	Mesh->SetCollisionProfileName(TEXT("ElectricObjectProfile"));	// �÷��̾��� ���� ������ �ޱ� ���� �ݸ��� ������ ����.

}

/// <summary>
/// ���Ͱ� �浹���� �� ȣ��Ǵ� �޼���
/// </summary>
/// <param name="MyComp"></param>
/// <param name="Other"></param>
/// <param name="OtherComp"></param>
/// <param name="bSelfMoved"></param>
/// <param name="HitLocation"></param>
/// <param name="HitNormal"></param>
/// <param name="NormalImpulse"></param>
/// <param name="Hit"></param>
void APPGear_Test::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("NotifyHit"));

	// �÷��̾�� �浹�ϸ�
	if (Other && Other->IsA(APPCharacterPlayer::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Hit"));

		APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(Other);
		if (Player != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Cast Completed to APPCharacterPlayer"));
			
			UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(Player);
			if (CharacterMovementComponent != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("Cast Completed to UCharacterMovementComponent"));

				float KnockbackStrength = 5.0f;
				FVector KnockbackDirection = -HitNormal * KnockbackStrength;

				CharacterMovementComponent->AddImpulse(KnockbackDirection);
			}
		}
		
	}

}

// Called when the game starts or when spawned
void APPGear_Test::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPGear_Test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

