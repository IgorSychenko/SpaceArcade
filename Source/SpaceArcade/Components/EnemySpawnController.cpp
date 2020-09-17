// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnController.h"
#include "Engine/World.h"
#include "SpaceArcade/Pawns/EnemyPawn.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

// Sets default values for this component's properties
UEnemySpawnController::UEnemySpawnController()
	:
	ChangeStageTimeMultiplier(1.0),
	ChangeEnemyMultiplier(1.0)
{
}


void UEnemySpawnController::StartSpawnStage()
{
	TArray<FEnemySpawnInfo> SpawnStages = GetCurrentSpawnStages();
	if (SpawnStages.Num() > 0) {
		EnemiesSpawn = 0;
		FRandomStream Random;
		Random.GenerateNewSeed();

		SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];

		SpawnEnemy();

		float TimeDelay = Random.RandRange(GetCurrentSpawnLevelInfo().StageMinDelay, GetCurrentSpawnLevelInfo().StageMaxDelay) * ChangeStageTimeMultiplier;
		GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnController::StartSpawnStage, TimeDelay, false);

		//UE_LOG(LogTemp, Log, TEXT("StartSpawnStage, TimeDelay = %f"), TimeDelay);
	}
}

void UEnemySpawnController::SpawnEnemy()
{	

	ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode->IsGameBegin) return;

	//UE_LOG(LogTemp, Log, TEXT("SpawnEnemy"));
	TArray<FEnemySpawnInfo> SpawnStages = GetCurrentSpawnStages();

	FActorSpawnParameters SpawnParameters;
	AEnemyPawn* EnemyPawn = GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParameters);

	EnemiesSpawn++;
	if (EnemiesSpawn < SpawnStage.NumOfEnemies) {
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawDelay * ChangeStageTimeMultiplier, false);
	}
}

// Called when the game starts
void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	ResetGameLevel();

	StartSpawnStage();
}

void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();

	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UEnemySpawnController::ResetGameLevel()
{
	GameLevel = 0;
}

void UEnemySpawnController::GameLevelUp()
{
	if (GameLevel < GetMaxGameLevel() - 2) {
		GameLevel++;
		OnLevelUp.Broadcast(GameLevel+1);
		UE_LOG(LogTemp, Log, TEXT("GameLevelUp = %i"), GameLevel);
	}
}