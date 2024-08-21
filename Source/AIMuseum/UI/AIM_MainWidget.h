// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "AIM_MainWidget.generated.h"

class UAIM_WelcomeWidget;
class UAIM_LoadingWidget;
class UAIM_ViewModel;

UCLASS()
class AIMUSEUM_API UAIM_MainWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show(EAIMuseumUIState State);
    void HideAll();
    void SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel);

    FOnPromptConfirmedSig& OnStartExperience() { return StartExperience; }
    FOnRandomRequestedSig& OnRandomRequested() { return RandomRequested; }

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
    FOnRandomRequestedSig RandomRequested;

    void OnPromptConfirmed();
    void OnRandomize();
};
