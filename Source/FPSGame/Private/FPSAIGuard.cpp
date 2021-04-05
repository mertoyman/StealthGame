// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"


#include "DrawDebugHelpers.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	 
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) return;

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (NoiseInstigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No instigator"));
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *NoiseInstigator->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%f"), Location.X);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Volume);
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

