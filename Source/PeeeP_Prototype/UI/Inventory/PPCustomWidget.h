// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPCustomWidget.generated.h"

/**
 * �÷��̾ �����ϱ� ���� ������ �Լ����� ���� Ŀ���� ����. �÷��̾ ������ �������� ����
 */
UCLASS()
class PEEEP_PROTOTYPE_API UPPCustomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	// ���� ������ �����ϰ� �ִ� ���� ����� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
};
