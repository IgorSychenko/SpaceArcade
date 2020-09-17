// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusTime.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/WorldSettings.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

void ABonusTime::BonusCollected_Implementation()
{
	ASpaceArcadeGameModeBase* GameMode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->ChangeTimeDilation(0.5, GameMode->PlayerRecoverTime);

	Super::BonusCollected_Implementation();
}

void ABonusTime::BonusDeactivate() {
	
}