// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESlotType: uint8
{
	ST_None,
	ST_InventoryParts,		// �κ��丮(����)
	ST_InventoryConsumable,	// �κ��丮(�Һ�)
	ST_InventoryOther,		// �κ��丮(��Ÿ)
};
