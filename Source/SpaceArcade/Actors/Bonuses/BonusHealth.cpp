// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusHealth.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

void ABonusHealth::BonusCollected_Implementation()
{
	ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddGameHealth();

	Super::BonusCollected_Implementation();
}
