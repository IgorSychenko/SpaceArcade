// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
	:
	ShootPeriod(1.0)
{

}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	StartShooting();
}

void UShootComponent::StartShooting() 
{
	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
}
void UShootComponent::StopShooting() {
	GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
}
void UShootComponent::Shoot() 
{
//	UE_LOG(LogTemp, Log, TEXT("Shoot"));
	ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode->IsGameBegin) return;

	for (FShootInfo ShootInfo : ShootInfos) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);//ShootInfo.Offset.RotateAngleAxis(GetOwner()->GetActorRotation().Yaw, FVector(0.0, 0.0, 1.0));
		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.0, ShootInfo.Angle, 0.0);
		AShootProjectile* ShootProjectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (ShootProjectile) {
			ShootProjectile->Damage = ShootInfo.Damage;
			ShootProjectile->SetShootNamePawn(GetOwner()->GetName());
		}
	}

}