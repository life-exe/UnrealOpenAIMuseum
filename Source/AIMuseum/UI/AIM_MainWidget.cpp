// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_MainWidget.h"
#include "UI/AIM_LoadingWidget.h"
#include "UI/AIM_WelcomeWidget.h"
#include "UI/AIM_ViewModel.h"

void UAIM_MainWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(WelcomeWidget);
    check(LoadingWidget);

    Widgets.Add(EAIMuseumUIState::Loading, LoadingWidget);
    Widgets.Add(EAIMuseumUIState::Welcome, WelcomeWidget);

    WelcomeWidget->OnPromptConfirmed().BindUObject(this, &ThisClass::OnPromptConfirmed);
    WelcomeWidget->OnRandomRequested().BindUObject(this, &ThisClass::OnRandomize);
}

void UAIM_MainWidget::OnPromptConfirmed()
{
    Show(EAIMuseumUIState::Loading);
    StartExperience.ExecuteIfBound();
}

void UAIM_MainWidget::OnRandomize()
{
    RandomRequested.ExecuteIfBound();
}

void UAIM_MainWidget::Show(EAIMuseumUIState InState)
{
    for (const auto& [State, Widget] : Widgets)
    {
        if (Widget)
        {
            const auto WidgetVisibility = State == InState  //
                                              ? ESlateVisibility::Visible
                                              : ESlateVisibility::Collapsed;
            Widget->SetVisibility(WidgetVisibility);
        }
    }

    if (InState == EAIMuseumUIState::Welcome)
    {
        WelcomeWidget->Show();
    }
}

void UAIM_MainWidget::HideAll()
{
    WelcomeWidget->SetVisibility(ESlateVisibility::Collapsed);
    LoadingWidget->FadeOut();
}

void UAIM_MainWidget::SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel)
{
    WelcomeWidget->SetViewModel(ViewModel);
    LoadingWidget->SetViewModel(ViewModel);
}
