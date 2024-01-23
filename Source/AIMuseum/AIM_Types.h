// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "AIM_Types.generated.h"

DECLARE_DELEGATE_OneParam(FOnPromptConfirmedSig, const FString&);

UENUM() enum class EAIMuseumUIState : uint8
{
    Welcome = 0,
    Loading
};
