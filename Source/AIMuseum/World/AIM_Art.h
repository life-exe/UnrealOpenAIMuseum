// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIM_Art.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class AIMUSEUM_API AAIM_Art : public AActor
{
    GENERATED_BODY()

public:
    AAIM_Art();

    void SetArtTexture(UTexture2D* ArtTexture);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<USceneComponent> Origin;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Plane;

private:
    UPROPERTY()
    UMaterialInstanceDynamic* ArtMaterial;
};
