// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddGamePoints(Points);

	Super::BonusCollected_Implementation();
}
