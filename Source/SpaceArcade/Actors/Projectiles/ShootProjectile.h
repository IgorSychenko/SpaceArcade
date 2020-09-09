// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ShootProjectile.generated.h"

UCLASS()
class SPACEARCADE_API AShootProjectile : public AActor
{
	GENERATED_BODY()

private:
	FString ShootNamePawn;
	
public:	
	// Sets default values for this actor's properties
	AShootProjectile();

	void SetShootNamePawn(FString NewName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting") USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting") UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting") UParticleSystemComponent* ShootParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting") float ProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting") float Damage;

	UFUNCTION(BlueprintCallable, Category = "Enemies") 
		void OnOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit);

};
