// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class SPACEARCADE_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void BonusCollected();
		virtual void BonusCollected_Implementation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		float MovingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* CollectParticle;


};
