// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_WelcomeWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI/AIM_ViewModel.h"

void UAIM_WelcomeWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(CreateButton);
    CreateButton->OnClicked.AddDynamic(this, &ThisClass::OnCreate);

    check(RandomizeButton);
    RandomizeButton->OnClicked.AddDynamic(this, &ThisClass::OnRandomize);

    check(PromptText);
    PromptText->SetFocus();
}

void UAIM_WelcomeWidget::OnCreate()
{
    PromptConfirmed.ExecuteIfBound();
}

void UAIM_WelcomeWidget::OnRandomize()
{
    RandomRequested.ExecuteIfBound();
}

void UAIM_WelcomeWidget::Show()
{
    PromptText->SetFocus();
}

void UAIM_WelcomeWidget::SetViewModel(TObjectPtr<UAIM_ViewModel> ViewModel)
{
    OnViewModelUpdated.Broadcast(ViewModel);
}
