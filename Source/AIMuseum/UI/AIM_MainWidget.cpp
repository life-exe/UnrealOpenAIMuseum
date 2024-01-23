// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_MainWidget.h"
#include "UI/AIM_LoadingWidget.h"
#include "UI/AIM_WelcomeWidget.h"

void UAIM_MainWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(WelcomeWidget);
    check(LoadingWidget);

    Widgets.Add(EAIMuseumUIState::Loading, LoadingWidget);
    Widgets.Add(EAIMuseumUIState::Welcome, WelcomeWidget);

    WelcomeWidget->OnPromptConfirmed().BindUObject(this, &ThisClass::OnPromptConfirmed);
}

void UAIM_MainWidget::OnPromptConfirmed(const FString& Prompt)
{
    Show(EAIMuseumUIState::Loading);
    LoadingWidget->SetPrompt(Prompt);
    StartExperience.ExecuteIfBound(Prompt);
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

void UAIM_MainWidget::SetError(const FString& ErrorMessage)
{
    WelcomeWidget->SetError(ErrorMessage);
}
