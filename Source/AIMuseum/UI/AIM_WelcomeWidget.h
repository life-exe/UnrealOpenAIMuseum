// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "AIM_WelcomeWidget.generated.h"

class UTextBlock;
class UButton;
class UEditableTextBox;

UCLASS()
class AIMUSEUM_API UAIM_WelcomeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();
    void SetError(const FString& Error);

    FOnPromptConfirmedSig& OnPromptConfirmed() { return PromptConfirmed; }

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> ErrorMessage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UButton> CreateButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UEditableTextBox> PromptText;

    virtual void NativeOnInitialized() override;

private:
    FOnPromptConfirmedSig PromptConfirmed;

    UFUNCTION()
    void OnCreate();

    UFUNCTION()
    void OnTextChanged(const FText& Text);
};
