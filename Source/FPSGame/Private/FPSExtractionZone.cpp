// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"



#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	OverlapComp->SetHiddenInGame(false);
	RootComponent = OverlapComp;

    DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
    DecalComp->DecalSize = FVector(200);
    DecalComp->SetupAttachment(RootComponent);
    
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (!MyPawn) { return; }

	if(MyPawn->bIsCarryingObjective)
	{
		AFPSGameMode* Gm = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (Gm)
		{
			Gm->CompleteMission(MyPawn);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	UE_LOG(LogTemp, Warning, TEXT("Overlap executes"));
}

