// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "LoadingWidget.h"

void ULoadingWidget::FadeOut()
{
    PlayAnimation(HideAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, true);
}

void ULoadingWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == HideAnim)
    {
        SetVisibility(ESlateVisibility::Collapsed);
    }
}
