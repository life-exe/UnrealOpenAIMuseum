// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIM_ExitPortal.generated.h"

class USceneComponent;
class UBoxComponent;

DECLARE_MULTICAST_DELEGATE(FOnExitExperienceSignature);

UCLASS()
class AIMUSEUM_API AAIM_ExitPortal : public AActor
{
    GENERATED_BODY()

public:
    AAIM_ExitPortal();

    FOnExitExperienceSignature& OnExitExperience() { return ExitExperience; }

protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<USceneComponent> Origin;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TObjectPtr<UBoxComponent> Box;

    virtual void BeginPlay() override;

private:
    FOnExitExperienceSignature ExitExperience;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
