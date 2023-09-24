// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "World/AIM_ExitPortal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AAIM_ExitPortal::AAIM_ExitPortal()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    Box = CreateDefaultSubobject<UBoxComponent>("Box");
    check(Box);
    Box->SetupAttachment(Origin);
}

void AAIM_ExitPortal::BeginPlay()
{
    Super::BeginPlay();

    Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
}

void AAIM_ExitPortal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA<ACharacter>())
    {
        ExitExperience.Broadcast();
    }
}
