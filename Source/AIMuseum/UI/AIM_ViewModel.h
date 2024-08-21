// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "AIM_ViewModel.generated.h"

UCLASS()
class AIMUSEUM_API UAIM_ViewModel : public UMVVMViewModelBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    FText Prompt;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    FText ErrorMessage;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    bool RandInProgress;

public:
    void SetPrompt(const FText& Prompt);
    FText GetPrompt() const;

    void SetErrorMessage(const FText& ErrorMessage);
    FText GetErrorMessage() const;

    void SetRandInProgress(bool RandInProgress);
    bool GetRandInProgress() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsPromptEmpty() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsErrorVisible() const;
};
