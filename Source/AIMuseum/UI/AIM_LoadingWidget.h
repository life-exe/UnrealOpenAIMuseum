// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIM_Types.h"
#include "AIM_LoadingWidget.generated.h"

class UTextBlock;
class UAIM_ViewModel;

UCLASS()
class AIMUSEUM_API UAIM_LoadingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void FadeOut();
    void SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel);

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> PromptText;

    UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> HideAnim;

    UPROPERTY(BlueprintAssignable)
    FOnViewModelUpdatedSig OnViewModelUpdated;

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
