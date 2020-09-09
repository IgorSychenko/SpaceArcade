// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	:
	Health(100.0),
	StartHealth(100.0)
{

}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = StartHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamaged);

}

void UHealthComponent::ChangeHealth(float Change)
{
	//if (Change == -100) return;
	Health += Change;
	if (Health <= 0.0) {
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamaged);
		
		OnHealthEnded.Broadcast(); 
	}
}

float UHealthComponent::GetHealth() {
	return Health;
}

void UHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController * Instigator, AActor * DamageCauser) {
	//if (Damage == 100) UE_LOG(LogTemp, Log, TEXT("Name damage object: %s, Health: %f, damage: %f"), *DamageCauser->GetName(), Health, Damage);
	ChangeHealth(-Damage);
}