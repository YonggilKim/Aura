// Fill out your copyright notice in the Description page of Project Settings.


#include "Chracter/AuraMonster.h"

AAuraMonster::AAuraMonster()
{
	Super::BeginPlay();
	UnHighlightActor();
}

void AAuraMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraMonster::HighlightActor()
{
	bHighLighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraMonster::UnHighlightActor()
{
	bHighLighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

}



