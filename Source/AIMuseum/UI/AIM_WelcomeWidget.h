// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "AIM_WelcomeWidget.generated.h"

class UButton;
class UEditableTextBox;
class UAIM_ViewModel;

UCLASS()
class AIMUSEUM_API UAIM_WelcomeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();
    void SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel);

    FOnPromptConfirmedSig& OnPromptConfirmed() { return PromptConfirmed; }
    FOnRandomRequestedSig& OnRandomRequested() { return RandomRequested; }

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> CreateButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> RandomizeButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UEditableTextBox> PromptText;

    UPROPERTY(BlueprintAssignable)
    FOnViewModelUpdatedSig OnViewModelUpdated;

    virtual void NativeOnInitialized() override;

private:
    FOnPromptConfirmedSig PromptConfirmed;
    FOnRandomRequestedSig RandomRequested;

    UFUNCTION()
    void OnCreate();

    UFUNCTION()
    void OnRandomize();
};
