// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObject/Electric/PPGear.h"
#include "Character/PPCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APPGear::APPGear()
{
	// �ؾ��� ��
	// 1. �浹 ó���� �ڽ� ������Ʈ �߰�
	// 2. �ش� �ڽ�������Ʈ�� �浹 �� �˹� ���(Overlap Begin����)
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽� ������Ʈ ����
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(false);								// ���� ������ ���� �ʴ´ٸ� �ݵ�� false�� ����.
	Mesh->SetCollisionProfileName(TEXT("ElectricObjectProfile"));	// �÷��̾��� ���� ������ �ޱ� ���� �ݸ��� ������ ����.

	bIsCharged = false;
}

/// <summary>
/// ���Ͱ� �浹���� �� ȣ��Ǵ� �޼���
/// ���� ������ �浹�Ǵ� ���� �߻�
/// </summary>
/// <param name="MyComp"></param>
/// <param name="Other"></param>
/// <param name="OtherComp"></param>
/// <param name="bSelfMoved"></param>
/// <param name="HitLocation"></param>
/// <param name="HitNormal"></param>
/// <param name="NormalImpulse"></param>
/// <param name="Hit"></param>
void APPGear::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	UE_LOG(LogTemp, Log, TEXT("NotifyHit"));
	UE_LOG(LogTemp, Log, TEXT("Hit Noraml: %f, %f, %f"), HitNormal.X, HitNormal.Y, HitNormal.Z);

	/*if (Other)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Other->GetRootComponent());
		if (PrimitiveComponent)
		{
			UE_LOG(LogTemp, Log, TEXT("Cast Completed"));
			FVector direction = FVector(-HitNormal.X, -HitNormal.Y, 0.0f);
			PrimitiveComponent->SetPhysicsLinearVelocity(direction * 500.f);
			PrimitiveComponent->SetPhysicsLinearVelocity(FVector::UpVector * 500.f, true);
		}
	}*/

	// �÷��̾�� �浹�ϸ�
	if (Other && Other->IsA(APPCharacterPlayer::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Hit"));
		if (!bIsCharged)
		{
			APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(Other);

			if (Player != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("Cast Completed to APPCharacterPlayer"));
				UCharacterMovementComponent* CharacterMovementComponent = Player->GetCharacterMovement();
				if (CharacterMovementComponent != nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("Succeed to Getting A UCharacterMovementComponent"));

					FVector dir = HitLocation - GetActorLocation();
					FVector normalDir = dir.GetSafeNormal2D();

					ApplyKnockback(CharacterMovementComponent, normalDir, 500.0f);
				}

				Player->TakeDamage(1.0f);
			}
		}
	}

}

// Called when the game starts or when spawned
void APPGear::BeginPlay()
{
	Super::BeginPlay();

}

/// <summary>
/// ĳ���͸� �˹��Ű�� �޼���
/// </summary>
/// <param name="CharacterMovementComponent">�˹��ų ĳ������ CharacterMovementComponent</param>
/// <param name="Direction">�˹� ����</param>
/// <param name="strength">�˹� ����</param>
void APPGear::ApplyKnockback(UCharacterMovementComponent* CharacterMovementComponent, FVector direction, float strength, bool bVelocityChange)
{
	// �˹��� ����ƽ �Ž��� ���߾� ��Ŀ�� Root�� ��� �� Root�� ��ġ�� �ε��� ĳ���Ϳ��� ���͸� ���ؼ� normalization ��Ų ���� strength�� ���Ͽ� �˹� ��ų ����
	// Character���� z Velocity�� �޾ƿ� strength���� ���̸�ŭ z�� �������� ���� �־� �����ϰ� �����ϴ� ������ ����.

	double ZVelocity = CharacterMovementComponent->Velocity.Z;

	FVector knockbackDir = FVector(direction.X, direction.Y, (strength - ZVelocity)/strength);

	FVector KnockbackDirection = knockbackDir * strength;
	CharacterMovementComponent->AddImpulse(KnockbackDirection, bVelocityChange);
}

void APPGear::Charge()
{
	bIsCharged = true;
	// �浹 ��Ȱ��ȭ
	Mesh->SetCollisionProfileName(TEXT("OverlapAll"));

	// ���� Ȱ��ȭ
	Mesh->SetSimulatePhysics(true);
}


// Called every frame
void APPGear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}