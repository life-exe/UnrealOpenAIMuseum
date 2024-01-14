// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "AIM_Types.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPromptConfirmedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModelUpdatedSignature, UVMAIMuseum*, Model);

UENUM()
enum class EAIMuseumUIState : uint8
{
    Welcome = 0,
    Loading
};
