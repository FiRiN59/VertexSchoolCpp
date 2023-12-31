// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class PLAYGROUND_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	UPROPERTY(VisibleAnywhere, Category="SwitchComponent")
	class UPointLightComponent *PointLight1;

	UPROPERTY(VisibleAnywhere, Category="SwitchComponent")
	class USphereComponent *Sphere1;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ToggleLight();

	UPROPERTY(VisibleAnywhere, Category="SwitchParameters")
	float DesiredIntensity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
