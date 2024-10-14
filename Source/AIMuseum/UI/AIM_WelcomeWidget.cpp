// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_WelcomeWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ComboBoxString.h"
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

    check(ImageModelComboBox);
    ImageModelComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnImageModelChanged);
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

void UAIM_WelcomeWidget::SetViewModel(TObjectPtr<UAIM_ViewModel> NewViewModel)
{
    check(NewViewModel);
    ViewModel = NewViewModel;

    ImageModelComboBox->ClearOptions();

    const auto ImageModels = NewViewModel->GetImageModelDisplayData();
    for (const auto& [ModelName, _] : ImageModels)
    {
        ImageModelComboBox->AddOption(ModelName);
    }
    ImageModelComboBox->SetSelectedOption(NewViewModel->GetImageModelDisplayText());

    OnViewModelUpdated.Broadcast(NewViewModel);
}

void UAIM_WelcomeWidget::OnImageModelChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (ViewModel.IsValid())
    {
        const auto ImageModels = ViewModel->GetImageModelDisplayData();
        if (ImageModels.Contains(SelectedItem))
        {
            ViewModel->SetImageModel(ImageModels[SelectedItem]);
        }
    }
}