// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceArcade/Pawns/EnemyPawn.h"
#include "EnemySpawnController.generated.h"


USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") FTransform SpawnTransform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies") TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies") int NumOfEnemies = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies") float SpawDelay = 2;

};

USTRUCT(BlueprintType)
struct FEnemySpawnLevelInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") TArray<FEnemySpawnInfo> SpawnStages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") float StageMinDelay = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") float StageMaxDelay = 6;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelUp, int, NewLevel);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawnController();

	void StartSpawnStage();
	void SpawnEnemy();

private:
	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;
	int EnemiesSpawn;
	FEnemySpawnInfo SpawnStage;
	int GameLevel;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Deactivate() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") TArray<FEnemySpawnLevelInfo> EnemySpawnLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") float ChangeStageTimeMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies") float ChangeEnemyMultiplier;

	UFUNCTION(BlueprintPure, Category = "SpawnLevel") inline int GetGameLevel() { return GameLevel+1; };
	UFUNCTION(BlueprintPure, Category = "SpawnLevel") inline int GetMaxGameLevel() { return EnemySpawnLevels.Num(); };
	UFUNCTION(BlueprintCallable, Category = "SpawnLevel") void ResetGameLevel();
	UFUNCTION(BlueprintCallable, Category = "SpawnLevel") void GameLevelUp();
	UFUNCTION(BlueprintPure, Category = "SpawnLevel") inline FEnemySpawnLevelInfo GetCurrentSpawnLevelInfo() { return EnemySpawnLevels[GameLevel]; };
	UFUNCTION(BlueprintPure, Category = "SpawnLevel") inline TArray<FEnemySpawnInfo> GetCurrentSpawnStages() { return EnemySpawnLevels[GameLevel].SpawnStages; };
	UPROPERTY(BlueprintAssignable, Category = "SpawnLevel") FLevelUp OnLevelUp;
};
