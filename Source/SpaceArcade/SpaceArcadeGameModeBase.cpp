// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceArcadeGameModeBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/GameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/WorldSettings.h"

ASpaceArcadeGameModeBase::ASpaceArcadeGameModeBase()
	:
	IsGameOver(false),
	PlayerRecoverTime(3.0),
	IncreaseDifficultyTime(15.0),
	IsGameBegin(false),
	CurrentShootLevel(-1)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	GameHealthComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("GameHealthComponent"));
}

void ASpaceArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetEngine()->SetMaxFPS(60);

	GameHealthComponent->OnHealthsEnded.AddDynamic(this, &ASpaceArcadeGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn) {
		ChangeShootLevel(true);
		PlayerPawn->OnPawnDamaged.AddDynamic(this, &ASpaceArcadeGameModeBase::ExplodePawn);
	}
	
	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &ASpaceArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyTime, true, IncreaseDifficultyTime);
}

void ASpaceArcadeGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	GameHealthComponent->ChangeHealth(-1);
	ChangeShootLevel(false);
	if (!IsGameOver) GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &ASpaceArcadeGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void ASpaceArcadeGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void ASpaceArcadeGameModeBase::EndGame()
{
	IsGameOver = true;
	EnemySpawnController->SetActive(false);
	OnGameOver.Broadcast();
	PlayerPawn->Destroy();

//	UE_LOG(LogTemp, Log, TEXT("GAME OVER!"));
}

void ASpaceArcadeGameModeBase::AddGamePoints(int Value)
{
	GamePoints += Value;
}

void ASpaceArcadeGameModeBase::ResetGamePoints()
{
	GamePoints = 0;
}

bool ASpaceArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
}

void ASpaceArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->GameLevelUp();
	// OFF
	//EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95, 0.2);
	//EnemySpawnController->ChangeEnemyMultiplier = EnemySpawnController->ChangeStageTimeMultiplier * 1.1;
//	UE_LOG(LogTemp, Log, TEXT("Difficulty: ChangeStageTimeMultiplier = %f, ChangeEnemyMultiplier= %f"), EnemySpawnController->ChangeStageTimeMultiplier, EnemySpawnController->ChangeEnemyMultiplier);
}

UFUNCTION(BlueprintCallable, Category = "Game") void ASpaceArcadeGameModeBase::AddGameHealth()
{
	GameHealthComponent->ChangeHealth(1);
}

void ASpaceArcadeGameModeBase::ChangeTimeDilation(float GameSpeed, float OnTime)
{
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5);
	AWorldSettings* const WorldSettings = GetWorld()->GetWorldSettings();
	WorldSettings->SetTimeDilation(GameSpeed);
	GetWorld()->GetTimerManager().SetTimer(BonusTimer, this, &ASpaceArcadeGameModeBase::ChangeTimeDilationStop, OnTime*GameSpeed, false);
//	UE_LOG(LogTemp, Log, TEXT("Game Speed = .5"));
}

void ASpaceArcadeGameModeBase::ChangeTimeDilationStop()
{
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0);
	AWorldSettings* const WorldSettings = GetWorld()->GetWorldSettings();
	WorldSettings->SetTimeDilation(1.0);
//	UE_LOG(LogTemp, Log, TEXT("Game Speed = 1"));
}