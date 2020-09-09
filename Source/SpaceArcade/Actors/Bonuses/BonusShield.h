// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceArcade/Actors/Bonuses/Bonus.h"
#include "SpaceArcade/Actors/Shield.h"
#include "BonusShield.generated.h"

/**
 *
 */
UCLASS()
class SPACEARCADE_API ABonusShield : public ABonus
{
	GENERATED_BODY()

protected:

	virtual void BonusCollected_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
		TSubclassOf<AShield> ShieldClass;

};
