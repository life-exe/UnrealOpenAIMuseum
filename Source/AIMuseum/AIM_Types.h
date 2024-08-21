// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "AIM_Types.generated.h"

DECLARE_DELEGATE(FOnPromptConfirmedSig);
DECLARE_DELEGATE(FOnRandomRequestedSig);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnViewModelUpdatedSig, UAIM_ViewModel*, ViewModel);

UENUM() enum class EAIMuseumUIState : uint8
{
    Welcome = 0,
    Loading
};
