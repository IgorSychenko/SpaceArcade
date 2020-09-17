// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
	:
	bAddPoints(true),
	EnemySpeed(200.0),
	PointsOnDestroy(10)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(PawnCollision);
	PawnCollision->SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::Kill);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
	for (FBonusChance Bonus : PossibleBonuses) {
		float RandChance = Random.RandRange(0.f, 100.f);
		//UE_LOG(LogTemp, Log, TEXT("Bonus: %s, Chance needed: %f, Chance random: %f"), *Bonus.BonusClass->GetName(), Bonus.Chance, RandChance);
		if (RandChance < Bonus.Chance) {
			//UE_LOG(LogTemp, Log, TEXT("Bonus spawned"));
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
			
			break; // Only 1 bonus per kill
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = EnemySpeed * DeltaTime;
	FVector TickMoving = FVector(WorldMoveOffset * GetActorRotation().Vector().X, WorldMoveOffset * GetActorRotation().Vector().Y, 0.f);
	AddActorWorldOffset(TickMoving);

}
// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::Kill() {
	//UE_LOG(LogTemp, Log, TEXT("Kill on health: %f"), HealthComponent->GetHealth());

	if (bAddPoints) {
		ASpaceArcadeGameModeBase* GameMode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (GameMode) GameMode->AddGamePoints(PointsOnDestroy);

		SpawnBonuses();
	}

	if (DestroyParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Log, TEXT("OnEnemyOverlap with %s, health: %f"), *OtherActor->GetName(), HealthComponent->GetHealth());

	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0)) {
		float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
		//UE_LOG(LogTemp, Log, TEXT("OnEnemyOverlap with player"), AppliedDamage);
		bAddPoints = false;
		if (AppliedDamage > 0.f) Kill();
	}
}
