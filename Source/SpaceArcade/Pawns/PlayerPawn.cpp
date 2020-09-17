// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/SpaceArcadeGameModeBase.h"

// Sets default values
APlayerPawn::APlayerPawn()
	:
	TourchMoveSensivity(1.0),
	MoveLimit(FVector2D(300.0, 300.0)),
	IsCanBeDamaged(true)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(PawnCollision);
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent, NAME_None);

	//CamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamSpringArm"));
	//CamSpringArm->SetupAttachment(RootComponent);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	//PawnCamera->SetupAttachment(CamSpringArm);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	/*ASpaceArcadeGameModeBase* Gamemode = Cast<ASpaceArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;
	ShootComponent->ShootInfos = Gamemode->ShootInfoLevels[0].ShootInfos;
	ShootComponent->ShootPeriod = Gamemode->ShootInfoLevels[0].ShootPeriod;*/
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PawnMaterial = PawnMesh->GetMaterials()[0];
}

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

bool APlayerPawn::CanBeDamaged_Implementation()
{
	return IsCanBeDamaged;
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!CanBeDamaged()) return 0.0;

	//UE_LOG(LogTemp, Log, TEXT("Player Take damage on %s"), *DamageCauser->GetName());

	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);

	OnPawnDamaged.Broadcast();

	return Damage;
}

void APlayerPawn::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	if (ShootComponent) ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);

	if (DestroyParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass())) {
		Component->Deactivate();
	}
}

void APlayerPawn::RecoverPawn_Implementation()
{
	SetActorEnableCollision(true);

	if (ShootComponent) ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass())) {
		Component->Activate(true);
	}
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (PlayerController) {
		bool Tourch; float TourchX; float TourchY;
		PlayerController->GetInputTouchState(ETouchIndex::Touch1, TourchX, TourchY, Tourch);

		if (Tourch) {
			float DeltaX = TourchLocation.X - TourchX;
			float DeltaY = TourchLocation.Y - TourchY;
			UE_LOG(LogTemp, Log, TEXT("Tourch: %f-%f"), DeltaX, DeltaY);

			FVector NewLocation = GetActorLocation();
			NewLocation.X = FMath::Clamp<float>(NewLocation.X + DeltaY, -500.0, 500.0);
			NewLocation.Y = FMath::Clamp<float>(NewLocation.Y - DeltaX, -600.0, 600.0);
			SetActorLocation(NewLocation);
			//AddActorLocalOffset(FVector(DeltaY, -DeltaX, 0));

			TourchLocation = FVector2D(TourchX, TourchY);
		}
	}*/
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Released, this, &APlayerPawn::OnTouchRelease);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	//UE_LOG(LogTemp, Log, TEXT("OnTouchPress: %s"), *Location.ToString());
	TourchLocation = FVector2D(Location);
	Tourching = true;
}
void APlayerPawn::OnTouchRelease(ETouchIndex::Type FingerIndex, FVector Location)
{
	//UE_LOG(LogTemp, Log, TEXT("OnTouchRelease: %s"), *Location.ToString());
	Tourching = false;
}
void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	float DeltaX = TourchLocation.X - Location.X;
	float DeltaY = TourchLocation.Y - Location.Y;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp<float>(NewLocation.X + DeltaY * TourchMoveSensivity, -MoveLimit.X/2, MoveLimit.X);
	NewLocation.Y = FMath::Clamp<float>(NewLocation.Y - DeltaX * TourchMoveSensivity, -MoveLimit.Y, MoveLimit.Y);
	SetActorLocation(NewLocation);
	//AddActorLocalOffset(FVector(DeltaY, -DeltaX, 0));

	TourchLocation = FVector2D(Location.X, Location.Y);
}