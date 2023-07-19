// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chracter/AuraChracterBase.h"
#include "../Interface/EnermyInterface.h"
#include "AuraMonster.generated.h"

/**
 *
 */
UCLASS()
class AURA_API AAuraMonster : public AAuraChracterBase, public IEnermyInterface
{
	GENERATED_BODY()
public:
	AAuraMonster();
	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
protected:
	UPROPERTY(BlueprintReadOnly)
		bool bHighLighted = false;

};
