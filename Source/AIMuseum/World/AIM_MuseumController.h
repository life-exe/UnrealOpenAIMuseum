// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Provider/CommonTypes.h"
#include "AIM_MuseumController.generated.h"

class AAIM_Art;
class UOpenAIProvider;
struct FImageResponse;
class AAIM_ExitPortal;
class APlayerStart;
class UMainWidget;
class UVMAIMuseum;

UCLASS()
class AIMUSEUM_API AAIM_MuseumController : public AInfo
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<AAIM_ExitPortal> ExitPortal;

    UPROPERTY(EditAnywhere)
    TObjectPtr<APlayerStart> PlayerStart;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UMainWidget> MainWidgetClass;

    UPROPERTY(EditAnywhere)
    bool bImageGenerationEnabled{true};

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<AAIM_Art*> Arts;

    UPROPERTY()
    TObjectPtr<UOpenAIProvider> Provider;

    UPROPERTY()
    TObjectPtr<UMainWidget> MainWidget;

    UPROPERTY()
    TObjectPtr<UVMAIMuseum> VMAIMuseum;

    FOpenAIAuth Auth;

    void RequestImages(const FString& Prompt, int32 NumOfImages);
    FString GeneratePrompt() const;
    void ShowWelcomeWidget();

    void OnCreateImageCompleted(const FImageResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);
    void OnExitExperience();

    UFUNCTION()
    void OnStartExperience();
};
