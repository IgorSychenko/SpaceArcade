// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceArcade/Components/ShootComponent.h"
#include "SpaceArcade/Components/HealthComponent.h"
#include "SpaceArcade/Actors/Bonuses/Bonus.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "EnemyPawn.generated.h"

USTRUCT (BlueprintType)
struct FBonusChance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		TSubclassOf<ABonus> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		float Chance;

};

UCLASS()
class SPACEARCADE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

private:
	bool bAddPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnBonuses();

	UFUNCTION() void Kill();
	UFUNCTION() void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy") float EnemySpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy") int PointsOnDestroy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UBoxComponent* PawnCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UStaticMeshComponent* PawnMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UHealthComponent* HealthComponent; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting") UShootComponent* ShootComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonus") TArray<FBonusChance> PossibleBonuses;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual") UParticleSystem* DestroyParticle;

};
