// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceArcade/Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") FVector Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") float Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting") TSubclassOf<AShootProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") float Damage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Shoot();

private:
	FTimerHandle ShootTimer;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") float ShootPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") TArray<FShootInfo> ShootInfos;

	UFUNCTION(BlueprintCallable, Category = "Shooting") void StartShooting();
	UFUNCTION(BlueprintCallable, Category = "Shooting") void StopShooting();
};
