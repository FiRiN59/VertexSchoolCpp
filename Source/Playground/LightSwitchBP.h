// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchBP.generated.h"

UCLASS()
class PLAYGROUND_API ALightSwitchBP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SwitchComponents")
	class UPointLightComponent *PointLight1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SwitchComponents")
	class USphereComponent *Sphere1;

	// Begin Overlap
	UFUNCTION(BlueprintNativeEvent, Category="SwitchFunctions")
	void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void OnComponentBeginOverlap_Implementation(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// End Overlap
	UFUNCTION(BlueprintNativeEvent, Category="SwitchFunctions")
	void OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
	virtual void OnComponentEndOverlap_Implementation(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	// Toggle Light
	UFUNCTION()
	void ToggleLight();

	// Intensity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SwitchParameters")
	float DesiredIntensity;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
