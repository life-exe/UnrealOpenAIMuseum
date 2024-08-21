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

bool UAIM_ViewModel::IsPromptEmpty() const
{
    return Prompt.IsEmpty();
}

bool UAIM_ViewModel::IsErrorVisible() const
{
    return !ErrorMessage.IsEmpty();
}
