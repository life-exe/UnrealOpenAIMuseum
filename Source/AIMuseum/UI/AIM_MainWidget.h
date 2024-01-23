// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "AIM_MainWidget.generated.h"

class UAIM_WelcomeWidget;
class UAIM_LoadingWidget;

UCLASS()
class AIMUSEUM_API UAIM_MainWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show(EAIMuseumUIState State);
    void HideAll();
    void SetError(const FString& ErrorMessage);
    FOnPromptConfirmedSig& OnStartExperience() { return StartExperience; }

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UAIM_WelcomeWidget> WelcomeWidget;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UAIM_LoadingWidget> LoadingWidget;

    virtual void NativeOnInitialized() override;

private:
    UPROPERTY()
    TMap<EAIMuseumUIState, TObjectPtr<UUserWidget>> Widgets;

    FOnPromptConfirmedSig StartExperience;

    void OnPromptConfirmed(const FString& Prompt);
};
