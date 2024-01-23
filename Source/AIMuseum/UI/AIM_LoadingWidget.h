// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_LoadingWidget.generated.h"

class UTextBlock;

UCLASS()
class AIMUSEUM_API UAIM_LoadingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPrompt(const FString& Prompt);
    void FadeOut();

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> PromptText;

    UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> HideAnim;

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
