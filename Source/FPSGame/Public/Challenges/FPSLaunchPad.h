// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	FVector LaunchVelocity;

	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	float LaunchPitchAngle;

	UPROPERTY(EditInstanceOnly, Category="Effects")
	class UParticleSystem* SpawnEffect;

	UFUNCTION()
	void HandleLaunch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};