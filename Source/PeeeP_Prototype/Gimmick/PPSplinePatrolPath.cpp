// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PPSplinePatrolPath.h"
#include "Components/SplineComponent.h"

//������ �� Spline�±� �������� bIsLoop , ActorToMoveClass , IsClosedLoop , Duration , bCanMoveActor ����

// Sets default values
APPSplinePatrolPath::APPSplinePatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APPSplinePatrolPath::BeginPlay()
{
	Super::BeginPlay();

	//������ ������ Ŭ������ �������� ���� ��� ����.
	if (ActorToMoveClass == nullptr) return; 
	
	//Spline ���� ��ġ�� ���� ����
	ActorToMove = GetWorld()->SpawnActor<AActor>(ActorToMoveClass, Spline->GetComponentTransform()); 

	if (ActorToMove != nullptr)
	{
		// ���� �ð� ����  GetTimeSeconds() : ������ ������ �� ������� ����� �ð��� ������.
		StartTime = GetWorld()->GetTimeSeconds();

		//���� �̵� ���� ����
		bCanMoveActor = true; 

		//���� ��� ���������� �̵�, ������ ��� ���������� �̵�.
		bIsMovingForward = true; 
	}
	
}


// Called every frame
void APPSplinePatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((ActorToMove == nullptr) || !bCanMoveActor) return;

	/*
	������ Duration �� ���� ���Ͱ� �̵��ϵ��� ������ «.
	���� ���� ��� �����ϴٰ� �и�(duration)�� ������ ��� ������ �� CurrentSplineTime ���� 1.0�� �ǰ�,
	Distance == Spline->GetSplineLength() �� �Ǿ� ���Ͱ� ������ ���������� �ǹ���.
	*/
	float CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / Spline->Duration; 
	float Distance = Spline->GetSplineLength() * CurrentSplineTime;

	//�������� ���
	if (bIsMovingForward) 
	{
		SetActorRotationAndLocation(Distance);

		//������ ���� ������ ���.
		if (Distance >= Spline->GetSplineLength())
		{

			//���� �ݺ��� ���
			if (bIsLoop)
			{
				/*
				IsClosedLoop �� ���� ���� ���� ������ �� ������ ����Ǿ� ���� �̾��� ������ ����.
				�� ��� ���������� �̵����� �ʰ� ��� ���������� �ݺ� �̵��Ѵ�.
				IsClosedLoop �� ������ ���� ���� �������� �� �������� ���ٰ� �ٽ� ���ƿ��� ���·� ���ö����� ��θ� �Դ� ���� �Ҷ��̴�. 
				�� ��� ������->������ �� �ݺ� �̵��Ѵ�.
				*/
				if (!Spline->IsClosedLoop()) 
				{
					//���� ������ �̵��� ���� ����
					bIsMovingForward = false;
				}

				//����� �ð� �����Ͽ� �ʱ�ȭ
				StartTime = GetWorld()->GetTimeSeconds();
				bCanMoveActor = true;
			}
			//���� �ݺ� �ƴ� ���
			else
			{
				bCanMoveActor = false;
			}
		}
	}
	//�������� ���
	else 
	{

		//�� �ڵ� ���� ������ �������� ���� Distance���� SplineLength�� ��� ���־� ������ �Ÿ����� ���´�.
		float ReverseDistance = Spline->GetSplineLength() - Distance;
		SetActorRotationAndLocation(ReverseDistance);

		//������ ���� ������ ���.
		if (ReverseDistance <= 0.0f)
		{

			//���� �ݺ��� ���
			if (bIsLoop)
			{
				if (!Spline->IsClosedLoop())
				{
					//���� ������ �̵��� ���� ����
					bIsMovingForward = true;
				}

				//����� �ð� �����Ͽ� �ʱ�ȭ
				StartTime = GetWorld()->GetTimeSeconds();
				bCanMoveActor = true;
			}
			//���� �ݺ� �ƴ� ���
			else
			{
				bCanMoveActor = false;
			}
		}
	}
}

//�ٸ� Ŭ�������� ��밡���ϵ��� �ӽ÷� ���� �Լ�
void APPSplinePatrolPath::MoveActor()
{
	bCanMoveActor = true;
}


//���͸� �̵�,ȸ����Ű�� ����.
void APPSplinePatrolPath::SetActorRotationAndLocation(float Distance)
{
	//Spline ���� (Tick���� ��� ������Ʈ �ǰ� �ִ�) Distance���� �������� ��ġ,ȸ������ ���´�.   
	FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FVector Direction = Spline->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();

	//���� ���鿡 �÷��̾ ��ġ��Ų��.
	UStaticMeshComponent* ActorMesh = ActorToMove->FindComponentByClass<UStaticMeshComponent>();
	ActorMesh->SetWorldLocationAndRotation(Position, Rotator, true);
}

