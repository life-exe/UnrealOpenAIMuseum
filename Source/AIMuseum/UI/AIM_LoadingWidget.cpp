// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_LoadingWidget.h"
#include "Components/TextBlock.h"
#include "UI/AIM_ViewModel.h"

void UAIM_LoadingWidget::FadeOut()
{
    PlayAnimation(HideAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, true);
}

void UAIM_LoadingWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == HideAnim)
    {
        SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UAIM_LoadingWidget::SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel)
{
    OnViewModelUpdated.Broadcast(ViewModel);
}
