// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_WelcomeWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI/AIM_ViewModel.h"
#include "Components/ComboBoxString.h"

void UAIM_WelcomeWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(CreateButton);
    CreateButton->OnClicked.AddDynamic(this, &ThisClass::OnCreate);

    check(RandomizeButton);
    RandomizeButton->OnClicked.AddDynamic(this, &ThisClass::OnRandomize);

    check(PromptText);
    PromptText->SetFocus();

    check(ImageComboBox);
    ImageComboBox->ClearOptions();
    for (const auto& [Key, Value] : ImageModels)
    {
        ImageComboBox->AddOption(Key);
    }
    ImageComboBox->SetSelectedOption("DALLE-2");
    ImageComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnImageModelChanged);
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

void UAIM_WelcomeWidget::SetViewModel(TObjectPtr<UAIM_ViewModel> InViewModel)
{
    ViewModel = InViewModel;
    OnViewModelUpdated.Broadcast(InViewModel);
}

void UAIM_WelcomeWidget::OnImageModelChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (ViewModel.IsValid() && ImageModels.Contains(SelectedItem))
    {
        ViewModel->SetImageModel(ImageModels[SelectedItem]);
    }
}
