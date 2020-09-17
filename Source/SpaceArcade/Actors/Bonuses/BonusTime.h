// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceArcade/Actors/Bonuses/Bonus.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BonusTime.generated.h"

/**
 * 
 */
UCLASS()
class SPACEARCADE_API ABonusTime : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusCollected_Implementation() override;

	void BonusDeactivate();

	FTimerHandle BonusTimer;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus") float BonusTime;
	
};
