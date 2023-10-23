// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchBP.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitchBP::ALightSwitchBP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DesiredIntensity = 5000.0f;

	// Set up the light
	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(true);
	RootComponent = PointLight1;

	// Sphere collision component
	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->SetHiddenInGame(false);

	// Overlap Events
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchBP::OnComponentBeginOverlap);
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchBP::OnComponentEndOverlap);	
}

// Called when the game starts or when spawned
void ALightSwitchBP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ALightSwitchBP::OnComponentBeginOverlap_Implementation(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchBP::OnComponentEndOverlap_Implementation(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchBP::ToggleLight()
{
	PointLight1->ToggleVisibility();
}
