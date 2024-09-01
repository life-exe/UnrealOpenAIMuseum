// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FuncLib/ModelTypes.h"
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

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    EImageModelEnum ImageModel{EImageModelEnum::DALL_E_2};

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    FText ImageProgressStatus;

public:
    void SetPrompt(const FText& Prompt);
    FText GetPrompt() const;

    void SetErrorMessage(const FText& ErrorMessage);
    FText GetErrorMessage() const;

    void SetRandInProgress(bool RandInProgress);
    bool GetRandInProgress() const;

    void SetImageModel(EImageModelEnum NewImageModel);
    EImageModelEnum GetImageModel() const;

    void SetImageProgressStatus(const FText& ImageProgressStatus);
    FText GetImageProgressStatus() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsPromptEmpty() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsErrorVisible() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsDalle3() const;
};
