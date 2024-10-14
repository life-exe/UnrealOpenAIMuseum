// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_ViewModel.h"

void UAIM_ViewModel::SetPrompt(const FText& NewPrompt)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(Prompt, NewPrompt))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsPromptEmpty);
    }
}

FText UAIM_ViewModel::GetPrompt() const
{
    return Prompt;
}

void UAIM_ViewModel::SetErrorMessage(const FText& NewErrorMessage)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(ErrorMessage, NewErrorMessage))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsErrorVisible);
    }
}

FText UAIM_ViewModel::GetErrorMessage() const
{
    return ErrorMessage;
}

void UAIM_ViewModel::SetRandInProgress(bool NewRandInProgress)
{
    UE_MVVM_SET_PROPERTY_VALUE(RandInProgress, NewRandInProgress);
}

bool UAIM_ViewModel::GetRandInProgress() const
{
    return RandInProgress;
}

void UAIM_ViewModel::SetImageModel(EImageModelEnum NewImageModel)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(ImageModel, NewImageModel))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ShouldShowImageLoadingProgress);
    }
}

EImageModelEnum UAIM_ViewModel::GetImageModel() const
{
    return ImageModel;
}

void UAIM_ViewModel::SetImageLoadingProgress(const FImageLoadingProgress& Progress)
{
    ImageLoadingProgress = Progress;
    UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ImageLoadingInfo);
}

bool UAIM_ViewModel::IsPromptEmpty() const
{
    return Prompt.IsEmpty();
}

bool UAIM_ViewModel::IsErrorVisible() const
{
    return !ErrorMessage.IsEmpty();
}

FText UAIM_ViewModel::ImageLoadingInfo() const
{
    const FString Status = FString::Format(TEXT("{0}/{1}"), {ImageLoadingProgress.CurrentNum, ImageLoadingProgress.Count});
    return FText::FromString(Status);
}

bool UAIM_ViewModel::ShouldShowImageLoadingProgress() const
{
    return ImageModel == EImageModelEnum::DALL_E_3;
}
