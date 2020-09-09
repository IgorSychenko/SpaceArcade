// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceArcade/Actors/Bonuses/Bonus.h"
#include "BonusHealth.generated.h"

/**
 * 
 */
UCLASS()
class SPACEARCADE_API ABonusHealth : public ABonus
{
	GENERATED_BODY()

protected:

	virtual void BonusCollected_Implementation() override;
	
};
