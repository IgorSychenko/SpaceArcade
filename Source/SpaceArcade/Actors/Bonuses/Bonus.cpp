// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/Pawns/PlayerPawn.h"

// Sets default values
ABonus::ABonus()
	:
	RotationSpeed(45.0),
	MovingSpeed(100.0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(35);
}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	//UE_LOG(LogTemp, Log, TEXT("Bonus overlap"));
	if (!OtherActor) return;
	if (!Cast<APlayerPawn>(OtherActor)) return;

	//UE_LOG(LogTemp, Log, TEXT("Bonus CHAR overlap"));
	BonusCollected();
}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);

	Destroy();
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(FVector(- MovingSpeed * DeltaTime, 0.f, 0.f));
	AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}
