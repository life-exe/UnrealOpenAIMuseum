// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "World/AIM_Art.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AAIM_Art::AAIM_Art()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
    check(Plane);
    Plane->SetupAttachment(Origin);
}

void AAIM_Art::BeginPlay()
{
    Super::BeginPlay();

    ArtMaterial = Plane->CreateAndSetMaterialInstanceDynamic(0);
}

void AAIM_Art::SetArtTexture(UTexture2D* ArtTexture)
{
    if (ArtTexture)
    {
        ArtMaterial->SetTextureParameterValue("Art", ArtTexture);
    }
}