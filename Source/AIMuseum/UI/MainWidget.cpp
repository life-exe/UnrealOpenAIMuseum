// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "MainWidget.h"
#include "LoadingWidget.h"
#include "UI/Model/VMAIMuseum.h"

void UMainWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(LoadingWidget);
    check(WelcomeWidget);

    Widgets.Add(EAIMuseumUIState::Loading, LoadingWidget);
    Widgets.Add(EAIMuseumUIState::Welcome, WelcomeWidget);

    WelcomeWidget->OnPromptConfirmed().AddDynamic(this, &ThisClass::OnPromptConfirmed);
}

void UMainWidget::OnPromptConfirmed()
{
    Show(EAIMuseumUIState::Loading);
    StartExperience.Broadcast();
}

void UMainWidget::SetModel(TObjectPtr<UVMAIMuseum> VMAIMuseum)
{
    OnModelUpdated.Broadcast(VMAIMuseum);
}

void UMainWidget::Show(EAIMuseumUIState InState)
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
}

void UMainWidget::HideAll()
{
    LoadingWidget->FadeOut();
    WelcomeWidget->SetVisibility(ESlateVisibility::Collapsed);
}
