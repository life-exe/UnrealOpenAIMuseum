// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Provider/CommonTypes.h"
#include "AIM_MuseumController.generated.h"

class AAIM_Art;
class UOpenAIProvider;
struct FImageResponse;

UCLASS()
class AIMUSEUM_API AAIM_MuseumController : public AInfo
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<AAIM_Art*> Arts;

    UPROPERTY()
    TObjectPtr<UOpenAIProvider> Provider;

    FOpenAIAuth Auth;

    void RequestImages(const FString& Prompt, int32 NumOfImages);

    void OnCreateImageCompleted(const FImageResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);
};
