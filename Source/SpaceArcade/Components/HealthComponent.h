// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health;

	UFUNCTION() void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health") float StartHealth;

	UFUNCTION(BlueprintCallable, Category = "Health") void ChangeHealth(float Change);
	UFUNCTION(BlueprintPure, Category = "Health") float GetHealth();
		
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthEndedEvent OnHealthEnded;
};
