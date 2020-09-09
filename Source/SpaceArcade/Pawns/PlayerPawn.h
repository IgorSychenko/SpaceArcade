// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SpaceArcade/Components/ShootComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class SPACEARCADE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchRelease(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

private:
	APlayerController* PlayerController;
	FVector2D TourchLocation;
	bool Tourching;
	UMaterialInterface* PawnMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UBoxComponent* PawnCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UStaticMeshComponent* PawnMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") USpringArmComponent* CamSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn") UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn") UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting") UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls") float TourchMoveSensivity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls") FVector2D MoveLimit;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Healths") bool IsCanBeDamaged;
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
		bool CanBeDamaged();
		bool CanBeDamaged_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
		void ExplodePawn();
		void ExplodePawn_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
		void RecoverPawn();
		void RecoverPawn_Implementation();

	UPROPERTY(BlueprintAssignable, Category = "Healths") FPawnDamagedEvent OnPawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual") UParticleSystem* DestroyParticle;

};
