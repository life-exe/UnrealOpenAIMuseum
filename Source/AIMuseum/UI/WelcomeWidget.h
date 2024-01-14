// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "WelcomeWidget.generated.h"

UCLASS()
class AIMUSEUM_API UWelcomeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnPromptConfirmedSignature& OnPromptConfirmed() { return PromptConfirmed; }

protected:
    UPROPERTY(BlueprintCallable)
    FOnPromptConfirmedSignature PromptConfirmed;
};
