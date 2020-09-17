// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"


void ABonusShootLevelUp::BonusCollected_Implementation()
{
	ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;

	Gamemode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();
}
