// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class SPACEARCADE_API AShield : public AActor
{
	GENERATED_BODY()


protected:

	FTimerHandle ShieldTimer;

	class APlayerPawn* ShildForPawn;

public:
	// Sets default values for this actor's properties
	AShield();

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(APlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
		float ShieldTime;
};
