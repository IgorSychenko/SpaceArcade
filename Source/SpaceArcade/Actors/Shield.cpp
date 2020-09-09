// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "SpaceArcade/Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AShield::AShield() 
	:
	ShieldTime(5.0)
{
}

void AShield::ActivateShield(APlayerPawn* PlayerPawn)
{
	if (!PlayerPawn) { Destroy(); return; }

	ShildForPawn = PlayerPawn;

	PlayerPawn->IsCanBeDamaged = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);
	AttachToActor(PlayerPawn, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &AShield::DeactivateShield, ShieldTime, false);

}

void AShield::DeactivateShield()
{
	if (!ShildForPawn) return;

	ShildForPawn->IsCanBeDamaged = true;

	Destroy();

}

