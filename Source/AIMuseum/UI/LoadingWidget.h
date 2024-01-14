// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

UCLASS()
class AIMUSEUM_API ULoadingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void FadeOut();

protected:
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> HideAnim;

private:
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
