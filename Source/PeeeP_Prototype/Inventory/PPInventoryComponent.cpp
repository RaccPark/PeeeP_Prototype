// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/PPInventoryComponent.h"
#include "Character/PPCharacterPlayer.h"
#include "Engine/AssetManager.h"


// Sets default values for this component's properties
UPPInventoryComponent::UPPInventoryComponent()
{
	bWantsInitializeComponent = true;

	MaxInventorySlotNum = 6;
	MaxItemNum = 1;

	// �ʱ� ������ ����
	PartsItems.Init(nullptr, MaxInventorySlotNum);
	ConsumableItems.Init(nullptr, MaxInventorySlotNum);
	OtherItems.Init(nullptr, MaxInventorySlotNum);

	CurrentSlotIndex = 0;
	UsingSlotIndex = -1;	// -1: ������
}

void UPPInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// �κ��丮 �ʱ�ȭ
	InitInventory();
}


void UPPInventoryComponent::ClearUsingItem()
{
	UsingSlotIndex = -1; // ���������� ����
	QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Hidden);
	// ���� ������

	UE_LOG(LogTemp, Log, TEXT("Parts Item Detached: %d Slot"), CurrentSlotIndex);
}

// Called when the game starts
void UPPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UPPInventoryComponent::AddItem(FName InItemName, int32 InItemQuantity, int32& OutItemQuantity)
{

	// ���������� �߰��ߴ����� ���� ��� ��ȯ�� ����
	bool bIsResult = false;

	// �ּ� �Ŵ��� �ҷ�����
	UAssetManager& Manager = UAssetManager::Get();

	// �ּ� ���̵� ����Ʈ �޾ƿ���
	TArray<FPrimaryAssetId> Assets;
	// �±� ������ �Ѱ��༭ ������ �±׸� ���� �ּµ��� ����� �迭�� ��ȯ����
	Manager.GetPrimaryAssetIdList(TEXT("PPPartsData"), Assets);

	// Ư�� ������ Ű ����
	FPrimaryAssetId Key;
	Key.PrimaryAssetType = TEXT("PPPartsData");
	Key.PrimaryAssetName = InItemName;

	// �ش� Ű�� �ּ��� �����Ѵٸ�
	if (Assets.Contains(Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Data"));

		// ������ ����
		UPPInventoryPartsItem* NewItem = NewObject<UPPInventoryPartsItem>();
		if (NewItem)
		{
			FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets.FindByKey(Key)[0]));
			if (AssetPtr.IsPending())
			{
				AssetPtr.LoadSynchronous();
			}
			UPPPartsDataBase* ItemData = Cast<UPPPartsDataBase>(AssetPtr.Get());
			if (ItemData)
			{
				NewItem->PartsData = ItemData;
				NewItem->ItemQuantity = InItemQuantity;
			}
			else
			{
				return bIsResult;
			}
		}

		// �ش� ������ Ÿ��(�� ������Ʈ������ ����)�� �κ��丮�� �� ĭ ã�� ������ �߰��ϱ�
		// �� ������Ʈ������ ������ Ÿ���� ������ �ְ�, �κ��丮 ���� ���� ������ �ֱ⿡ �׳� �κ��丮 ���Կ� �ϳ� �߰��Ѵٰ� ���� �ȴ�.
		int32 Index = 0;
		switch (NewItem->PartsData->ItemType)
		{
		case EItemType::IT_Parts:
			for (UPPInventoryPartsItem* Item : PartsItems)
			{
				if (!IsValid(Item))
				{
					PartsItems[Index] = NewItem;	// ?
					bIsResult = true;
					OnChangeInven.Broadcast();
					break;
				}
				Index++;
			}
			break;
		}
		

		if (!bIsResult)
		{
			OutItemQuantity = NewItem->ItemQuantity;
			QuickSlotWidget->UpdateQuickSlot();
			return bIsResult;
		}
		else
		{
			QuickSlotWidget->UpdateQuickSlot();
			return bIsResult;
		}
	}

	OutItemQuantity = InItemQuantity;

	return bIsResult;
}

void UPPInventoryComponent::UseItem(int32 InSlotIndex, ESlotType InventoryType)
{
	/// ������ ��� �Լ������� ������ ������ Ÿ�԰� �ε����� �޾ƿͼ� �ش� �κ��丮�� �������� ����ϴ� ������ �߰��� ���Դϴ�.
	/// �����ε� �Һ� �����۸� ����� �� ������ Ȥ�� ���� Switch���� ����� Ÿ�Ժ��� ������ �������ֵ��� �����߽��ϴ�. (ex.���� ���� ��)
	/// ������ ��� �Լ��� ���� ���ȿ� �ݿ��� ���� ���� �� ���� �÷��̾��� �Լ��� ȣ���ϴ� ������ ���� ������ ��ҽ��ϴ�.
	/// �Һ� ������ ��� �� ������ ���ҽ�Ű��, ���� ���� ���� 0�̶�� �ش� �������� �Ҹ�����ֵ��� �Ͽ����ϴ�.
	/// https://velog.io/@apth1023/13.-12.-%EC%95%84%EC%9D%B4%ED%85%9C-%EC%9D%B8%EB%B2%A4%ED%86%A0%EB%A6%AC-%EC%8B%9C%EC%8A%A4%ED%85%9C-2
	
	switch (InventoryType)
	{
	case ESlotType::ST_InventoryParts:
		if (PartsItems.IsValidIndex(InSlotIndex) && IsValid(PartsItems[InSlotIndex]))
		{
			// ������ �پ��� �� ������, �ƴϸ� ����Ѵٴ� flag�� �� �������� ���� ����
			// ��� ���� ���̸� ������ flag�ϴ� ���� �±��ѵ� �ϴ� ������ �Ѵٰ� ����.
			// PartsItems[InSlotIndex]->ItemQuantity--;

			// ������ ���
			UE_LOG(LogTemp, Warning, TEXT("Parts Item Use"));

			// ������ 0 ���϶�� �Ҹ�����ִ� �κ�
			// �� ������Ʈ������ ������ �Ҹ�Ǹ� �ȵǹǷ� �������� ����.
		}
		break;
	}
	
}

void UPPInventoryComponent::UseItemCurrentIndex(ESlotType InventoryType)
{
	switch (InventoryType)
	{
	case ESlotType::ST_InventoryParts:
		if (PartsItems.IsValidIndex(CurrentSlotIndex) && IsValid(PartsItems[CurrentSlotIndex]))
		{
			// ������ ���
			UE_LOG(LogTemp, Log, TEXT("Trying Parts Item Use: %d Slot"), CurrentSlotIndex);

			/////////////////////////////////////////////////////////////////////////////////////
			/// ����ؾ� �� ����
			/// 1. ������ ������ �������� �ʾҴٸ�, �����Ǿ�� �ϸ� ���� �ϴ� "E" �ؽ�Ʈ�� ǥ��Ǿ�� ��.
			/// 2. ���� ���� �����ϰ��� �ϴ� ������ ������ ������ �ٸ���, ���� �����Ǿ��ִ� ������ �����ϰ� �� ������ �����ؾ� ��.
			/// �� �� "E" �ؽ�Ʈ�� ���� �ڵ�� visible ��ȯ �ʿ� ����(���õ�(ȭ�鿡 ǥ�õ�) ������ ���� ��� ������ �����̹Ƿ�)
			/// 3. ���� ���� �����ϰ��� �ϴ� ������ ������ ������ ���ٸ�, ���� �����Ǿ��ִ� ������ �����ؾ� ��.
			/// �� �� "E" �ؽ�Ʈ�� ǥ�Ⱑ ���� �ʾƾ� ��.
			///
			/// �� ��� ���׿��� ������ ���� �ǹ��� �߻��� �� ����.
			/// a. �����ϰ� �ִ� ������ ���� ������ ��� ���� ���ΰ�?
			/// b. �ε����θ� �����Ѵٸ� ������Ʈ ���� �ε����� ���� ������ �����ϰ� �ִ� ������ ���ٴ� ���� ������ �� �ִ°�?
			/// c. ������ ������ ��� ������ ���ΰ�?
			///		c-1. ex. GrabParts
			///				PartsItems[0]->PartsData->PartsComponent �� PPGrabParts Class(�ڷ��� TObjectPtr<UClass>)�� ����.
			///		�÷��̾ �����ϴ� ���(����):
			///			UActorComponent* PartsComponent = AddComponentByClass(UPPGrabParts::StaticClass(), true, FTransform::Identity, false);
			///			Parts = CastChecked<UPPPartsBase>(PartsComponent);
			/////////////////////////////////////////////////////////////////////////////////////

			/// �ε��� ���� ���

			APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(GetOwner());
			if (UsingSlotIndex == -1)	// ������ ������ �������� �ʾҴٸ�
			{
				UsingSlotIndex = CurrentSlotIndex;
				QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Visible);
				// ���� ������
				
				if (Player)
				{
					Player->SwitchParts(PartsItems[UsingSlotIndex]->PartsData);
				}

				UE_LOG(LogTemp, Log, TEXT("Parts Item Attached: %d Slot"), CurrentSlotIndex);
			}
			else if (UsingSlotIndex == CurrentSlotIndex)	// ���� ����ϰ� �ִ� ������ ���� ����Ϸ��� ������ ���ٸ�(��, ���� ����)
			{
				UsingSlotIndex = -1; // ���������� ����
				QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Hidden);
				// ���� ������
				
				if (Player)
				{
					Player->RemoveParts();
					Player->SetDefaultMeshAndAnim();
				}

				UE_LOG(LogTemp, Log, TEXT("Parts Item Detached: %d Slot"), CurrentSlotIndex);
			}
			else	// ���� ����ϰ� �ִ� ������ ���� ����Ϸ��� ������ �ٸ��ٸ�
			{
				UsingSlotIndex = CurrentSlotIndex;
				QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Visible);
				// ���� ��ü��
				
				if (Player)
				{
					Player->SwitchParts(PartsItems[UsingSlotIndex]->PartsData);
				}

				UE_LOG(LogTemp, Log, TEXT("Parts Item Attached: %d Slot"), CurrentSlotIndex);
			}
			Player->PlayEquipEffect();
		}
		break;
	}
	
}

void UPPInventoryComponent::RemoveItem(int32 InSlotIndex, ESlotType InventoryType)
{
	// �ش� �κ��丮 ������ ��ȿ���� üũ�ϰ� �Ҹ�����ش�.
	switch (InventoryType)
	{
	case ESlotType::ST_None:
		break;
	case ESlotType::ST_InventoryParts:
		if (PartsItems.IsValidIndex(InSlotIndex) && IsValid(PartsItems[InSlotIndex]))
		{
			PartsItems[InSlotIndex] = nullptr;
		}
		break;
	case ESlotType::ST_InventoryConsumable:
		break;
	case ESlotType::ST_InventoryOther:
		break;
	default:
		break;
	}
}

void UPPInventoryComponent::SwapItem(int32 InprevIndex, int32 InCurrentIndex)
{
	// ���� �κ��丮 ������ ��ü ����� ���� �� ���� ����
}

void UPPInventoryComponent::SortItem()
{
	// ���� �κ��丮 ������ ���� ��� ���� ����
}

void UPPInventoryComponent::InitInventory()
{
	// ������ �ִ� �������� ��� ������ ���ΰ�?

	// ���� �Ŵ��� �̱��� �ҷ�����
	UAssetManager& Manager = UAssetManager::Get();

	// ���� ���̵� ����Ʈ �޾ƿ���
	TArray<FPrimaryAssetId> Assets;
	// �±� ������ �Ѱ��༭ ������ �±׸� ���� �ּµ��� ����� �迭�� ��ȯ����
	Manager.GetPrimaryAssetIdList(TEXT("PPPartsData"), Assets);

	if (Assets.Num() > 0)
	{
		// Slot Index, <����, ����>
		TMap<int32, TPair<FName, int32>> InventoryPartsArray;
		//TMap<int32, TPair<FName, int32>> InventoryConstableArray;
		
		// �׽�Ʈ ���(�����δ� ����� ���Ͽ��� �����͸� �о�;� ��)
		{
			//InventoryPartsArray.Add(0, { TEXT("GrabPartsData"), 1 });
		}

		for (const auto& InvItem : InventoryPartsArray)
		{
			// Ư�� ������ Ű ����
			FPrimaryAssetId Key(TEXT("PPPartsData"), InvItem.Value.Key);

			if (Assets.Contains(Key))
			{
				// ������ ����
				UPPInventoryPartsItem* NewItem = NewObject<UPPInventoryPartsItem>();
				if (NewItem)
				{
					FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets.FindByKey(Key)[0]));
					if (AssetPtr.IsPending())
					{
						AssetPtr.LoadSynchronous();
					}
					UPPPartsDataBase* ItemData = Cast<UPPPartsDataBase>(AssetPtr.Get());
					if (ItemData)
					{
						NewItem->PartsData = ItemData;
						NewItem->ItemQuantity = InvItem.Value.Value;
						// ������ �ֱ�
						PartsItems[InvItem.Key] = NewItem;
					}
				}
			}
		}
	}


}

// Called every frame
void UPPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPPInventoryComponent::ModifyCurrentSlotIndex(int32 Value)
{
	CurrentSlotIndex += Value;

	// �ε��� ����
	CurrentSlotIndex = FMath::Clamp(CurrentSlotIndex, 0, PartsItems.Num() - 1);

	Slots = QuickSlotWidget->GetSlots();
	for (auto& item : Slots)
	{
		item->SetVisibility(ESlateVisibility::Hidden);
	}
	Slots[CurrentSlotIndex]->SetVisibility(ESlateVisibility::Visible);

	if (CurrentSlotIndex == UsingSlotIndex)
	{
		QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Visible);
	}
	else
	{
		QuickSlotWidget->SetEquipmentTextVisible(ESlateVisibility::Hidden);
	}

	UE_LOG(LogTemp, Log, TEXT("Current Slot Index: %d"), CurrentSlotIndex);	
}

void UPPInventoryComponent::SetQuickSlotWidget(UPPQuickSlotWidget* widget)
{
	if (widget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetQuickSlotWidget() Error!, The Parameter was a nullptr."));
		return;
	}
	QuickSlotWidget = widget;
	UE_LOG(LogTemp, Log, TEXT("Successfully getting QuickSlotWidget."));
}

