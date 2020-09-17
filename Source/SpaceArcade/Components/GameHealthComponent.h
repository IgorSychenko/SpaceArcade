// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthsEndedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthsChangedEvent, int, HealthChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameHealthComponent();

private:
	int Health;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Game Health")
		void ChangeHealth(int HealthChange);
	UFUNCTION(BlueprintPure, Category = "Game Health")
		int GetHealth();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Health") int StartHealths;

	UPROPERTY(BlueprintAssignable, Category = "Game Health") FHealthsEndedEvent OnHealthsEnded;
	UPROPERTY(BlueprintAssignable, Category = "Game Health") FHealthsChangedEvent OnHealthsChanged;
};
