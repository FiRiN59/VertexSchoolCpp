// Fill out your copyright notice in the Description page of Project Settings.


#include "AFloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	FloatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FloatMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (MeshAsset.Succeeded())
		FloatMesh->SetStaticMesh(MeshAsset.Object);
		FloatMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	const float RunningTime = GetGameTimeSinceCreation();
	const float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	const float DeltaRotation = DeltaTime * RotationSpeed;

	NewLocation.Z += DeltaHeight * FloatSpeed;
	NewRotation.Yaw += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotation);
}

