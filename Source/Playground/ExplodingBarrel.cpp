// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingBarrel.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AExplodingBarrel::AExplodingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	HitPoints = 10.0f;
	ExplosionDamage = 5.0f;
	ExplosionRadius = 200.0f;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrlMesh"));
	RootComponent = BarrelMesh;
	
	FireParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystemComponent"));
	FireParticleSystemComponent->SetupAttachment(RootComponent);
	FireParticleSystemComponent->bAutoActivate = false;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = 100000.0f;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->bIgnoreOwningActor = false;

	OnTakeAnyDamage.AddDynamic(this, &AExplodingBarrel::OnDamageTaken);
}

AExplodingBarrel::~AExplodingBarrel()
{
	if (const UWorld* World = GetWorld(); World && World->GetTimerManager().IsTimerActive(CountDownTimerHandle))
	{
		World->GetTimerManager().ClearTimer(CountDownTimerHandle);
	}
}

// Called when the game starts or when spawned
void AExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplodingBarrel::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage >= 0.f && HitPoints >= 0.f)
	{
		HitPoints -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Damage taken, Hitpoints: %f"), HitPoints);

		if (!FireParticleSystemComponent->IsActive())
		{
			FireParticleSystemComponent->Activate();
		}

		// Start the timer
		if (!GetWorld()->GetTimerManager().IsTimerActive(CountDownTimerHandle))
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting Countdown Timer"));
			GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &AExplodingBarrel::Countdown, 1.0f, true);
		}
	}

	if (HitPoints <= 0.f)
	{
		// Stop fire if it is active
		if (FireParticleSystemComponent->IsActive())
		{
			FireParticleSystemComponent->Deactivate();
		}

		const FVector ExplosionLocation = GetActorLocation();

		UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, ExplosionLocation, ExplosionRadius, nullptr, TArray<AActor*>(), this);

		if (RadialForce != nullptr)
		{
			RadialForce->Activate();
			RadialForce->FireImpulse();
		}

		// Play Explosion sound and particle system
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, ExplosionLocation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, ExplosionLocation);

		Destroy();
	}
}

void AExplodingBarrel::Countdown()
{
	HitPoints--;
	UE_LOG(LogTemp, Warning, TEXT("Countdown called. Hitpoints: %f"), HitPoints);

	if (HitPoints < 0.f)
	{
		OnDamageTaken(this, 0.0f, nullptr, nullptr, nullptr);
	}
}



