// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Sound/SoundCue.h"
#include "ExplodingBarrel.generated.h"

UCLASS(Blueprintable)
class PLAYGROUND_API AExplodingBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplodingBarrel();
	virtual ~AExplodingBarrel() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exploding Barrel")
	float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exploding Barrel")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exploding Barrel")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UParticleSystemComponent* FireParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	UParticleSystem* FireParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	URadialForceComponent* RadialForce;

	UFUNCTION()
	void OnDamageTaken(AActor *DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle CountDownTimerHandle;

	void Countdown();
};
