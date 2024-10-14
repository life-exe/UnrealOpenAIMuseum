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
    EImageModelEnum ImageModel{EImageModelEnum::DALL_E_3};

public:
    struct FImageLoadingProgress
    {
        int32 CurrentNum;
        int32 Count;
    };

    void SetPrompt(const FText& Prompt);
    FText GetPrompt() const;

    void SetErrorMessage(const FText& ErrorMessage);
    FText GetErrorMessage() const;

    void SetRandInProgress(bool RandInProgress);
    bool GetRandInProgress() const;

    void SetImageModel(EImageModelEnum ImageModel);
    EImageModelEnum GetImageModel() const;

    void SetImageLoadingProgress(const FImageLoadingProgress& Progress);

    TMap<FString, EImageModelEnum> GetImageModelDisplayData() const { return ImageModelDisplayData; }
    FString GetImageModelDisplayText() const
    {
        for (const auto& [DisplayText, DisplayImageModel] : ImageModelDisplayData)
        {
            if (ImageModel == DisplayImageModel)
            {
                return DisplayText;
            }
        }
        checkNoEntry();
        return FString{};
    }

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsPromptEmpty() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsErrorVisible() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    FText ImageLoadingInfo() const;

    UFUNCTION(BlueprintPure, FieldNotify)
    bool ShouldShowImageLoadingProgress() const;

private:
    FImageLoadingProgress ImageLoadingProgress;

    const TMap<FString, EImageModelEnum> ImageModelDisplayData{//
        {"DALLE-2", EImageModelEnum::DALL_E_2}, {"DALLE-3", EImageModelEnum::DALL_E_3}};
};
