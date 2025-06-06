﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PPAnimInstance.h"
#include "PPParkourAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PEEEP_PROTOTYPE_API UPPParkourAnimInstance : public UPPAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<class APPCharacterPlayer> CharacterPlayer;
	
public:
	UPPParkourAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ParkruParts")
	bool bIsCharging;
};
