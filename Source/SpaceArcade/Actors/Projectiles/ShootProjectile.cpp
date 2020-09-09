// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceArcade/Pawns/EnemyPawn.h"

// Sets default values
AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(1000.0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");

	ShootParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootParticle"));
	ShootParticle->SetupAttachment(Collision);
}

void AShootProjectile::SetShootNamePawn(FString NewName)
{
	ShootNamePawn = NewName;
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()) Collision->IgnoreActorWhenMoving(GetOwner(), true);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnOverlap);
}

// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed*DeltaTime, 0.0, 0.0));
}

void AShootProjectile::OnOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit) 
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return; // If not overlapped actor or it is not pawn
	if (GetOwner()) {
//		UE_LOG(LogTemp, Log, TEXT("ShootProjectile OnOverlaped. ShootNamePawn = %s, OtherActor = %s"), ShootNamePawn, *OtherActor->GetName());

		APawn* PawnOwner = Cast<APawn>(GetOwner());
		if (!PawnOwner) return;

		if (ShootNamePawn == *OtherActor->GetName()) return;

		// не должны попадать друг в друга
		AEnemyPawn* OtherEnemy = Cast<AEnemyPawn>(OtherActor);
		AEnemyPawn* OwnerEnemy = Cast<AEnemyPawn>(GetOwner());
		if (OtherEnemy && OwnerEnemy) return;

		AController* instigator = PawnOwner->GetController();
		UGameplayStatics::ApplyDamage(OtherActor, Damage, instigator, this, UDamageType::StaticClass());

		Destroy();
	}
}

