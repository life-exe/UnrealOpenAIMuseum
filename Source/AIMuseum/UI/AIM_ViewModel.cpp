// AI Museum, Copyright LifeEXE. All Rights Reserved.
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

void UAIM_ViewModel::SetImageModel(EImageModelEnum NewImageModel)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(ImageModel, NewImageModel))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsDalle3);
    }
}

EImageModelEnum UAIM_ViewModel::GetImageModel() const
{
    return ImageModel;
}

void UAIM_ViewModel::SetImageProgressStatus(const FText& NewImageProgressStatus)
{
    UE_MVVM_SET_PROPERTY_VALUE(ImageProgressStatus, NewImageProgressStatus);
}

FText UAIM_ViewModel::GetImageProgressStatus() const
{
    return ImageProgressStatus;
}

bool UAIM_ViewModel::GetRandInProgress() const
{
    return RandInProgress;
}

bool UAIM_ViewModel::IsPromptEmpty() const
{
    return Prompt.IsEmpty();
}

bool UAIM_ViewModel::IsErrorVisible() const
{
    return !ErrorMessage.IsEmpty();
}

bool UAIM_ViewModel::IsDalle3() const
{
    return ImageModel == EImageModelEnum::DALL_E_3;
}
