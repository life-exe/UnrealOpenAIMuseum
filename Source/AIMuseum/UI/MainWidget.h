// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WelcomeWidget.h"
#include "AIM_Types.h"
#include "MainWidget.generated.h"

class ULoadingWidget;
class UVMAIMuseum;

UCLASS()
class AIMUSEUM_API UMainWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UWelcomeWidget> WelcomeWidget;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<ULoadingWidget> LoadingWidget;

    UPROPERTY(BlueprintAssignable)
    FOnModelUpdatedSignature OnModelUpdated;

    virtual void NativeOnInitialized() override;

public:
    void SetModel(TObjectPtr<UVMAIMuseum> VMAIMuseum);

    void Show(EAIMuseumUIState State);
    void HideAll();

    FOnPromptConfirmedSignature& OnStartExperience() { return StartExperience; }

private:
    UPROPERTY()
    TMap<EAIMuseumUIState, UUserWidget*> Widgets;

    FOnPromptConfirmedSignature StartExperience;

    UFUNCTION()
    void OnPromptConfirmed();
};
