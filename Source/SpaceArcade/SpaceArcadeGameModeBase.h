// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceArcade/Components/EnemySpawnController.h"
#include "SpaceArcade/Components/GameHealthComponent.h"
#include "SpaceArcade/Components/ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Pawns/PlayerPawn.h"
#include "SpaceArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float ShootPeriod;

};

/**
 * 
 */
UCLASS()
class SPACEARCADE_API ASpaceArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ASpaceArcadeGameModeBase();

	virtual void BeginPlay() override;

protected:
	FTimerHandle RecoverTimer;
	bool IsGameOver;
	FTimerHandle IncreaseDifficultyTimer;
	FTimerHandle BonusTimer;

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void ExplodePawn();
		void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void RecoverPawn();
		void RecoverPawn_Implementation();

	void ChangeTimeDilationStop();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies") UEnemySpawnController* EnemySpawnController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Health") UGameHealthComponent* GameHealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game") float PlayerRecoverTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game") float IncreaseDifficultyTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game") APlayerPawn* PlayerPawn;
	UPROPERTY(BlueprintReadOnly, Category = "Game") int GamePoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game") bool IsGameBegin;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting") TArray<FShootInfoLevel> ShootInfoLevels;
	UPROPERTY(BlueprintReadOnly, Category = "Shooting")	int CurrentShootLevel;

	UFUNCTION(BlueprintCallable, Category = "Game") void EndGame();
	UFUNCTION(BlueprintCallable, Category = "Game") void AddGamePoints(int Value);
	UFUNCTION(BlueprintCallable, Category = "Game") void ResetGamePoints();
	UFUNCTION(BlueprintCallable, Category = "Game")	bool ChangeShootLevel(bool Up);
	UFUNCTION(BlueprintCallable, Category = "Game")	void IncreaseDifficulty();
	UFUNCTION(BlueprintCallable, Category = "Game") void AddGameHealth();
	UFUNCTION(BlueprintCallable, Category = "Game") void ChangeTimeDilation(float GameSpeed, float OnTime);
	
	UPROPERTY(BlueprintAssignable, Category = "Game") FGameOverEvent OnGameOver;
};
