// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SpaceArcade/Pawns/PlayerPawn.h"
#include "SpaceArcade/Actors/Shield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);

	if (!PlayerPawn && !PlayerPawn->IsCanBeDamaged) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerPawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AShield* Shield = GetWorld()->SpawnActor<AShield>(ShieldClass, SpawnParams);

	if (Shield) Shield->ActivateShield(PlayerPawn);

	Super::BonusCollected_Implementation();
}