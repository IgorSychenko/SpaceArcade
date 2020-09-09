// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent()
	:
	StartHealths(3)
{

	// ...
	Health = StartHealths;
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//if (PlayerPawn) {
		//PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UGameHealthComponent::OnPlayerDamaged); 
	/*} else {
		UE_LOG(LogTemp, Error, TEXT("No player pawn - UGameHealthComponent::BeginPlay"));
	}*/
}

void UGameHealthComponent::ChangeHealth(int HealthChange)
{
	Health += HealthChange;
	OnHealthsChanged.Broadcast(HealthChange);
	if (Health <= 0) {
		OnHealthsEnded.Broadcast();
	}
}

int UGameHealthComponent::GetHealth()
{
	return Health;
}