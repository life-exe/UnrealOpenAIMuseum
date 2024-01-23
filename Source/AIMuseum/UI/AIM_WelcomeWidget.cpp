// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "UI/AIM_WelcomeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UAIM_WelcomeWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(CreateButton);
    CreateButton->OnClicked.AddDynamic(this, &ThisClass::OnCreate);

    check(PromptText);
    PromptText->OnTextChanged.AddDynamic(this, &ThisClass::OnTextChanged);
    PromptText->SetFocus();

    OnTextChanged(PromptText->GetText());
}

void UAIM_WelcomeWidget::OnCreate()
{
    PromptConfirmed.ExecuteIfBound(PromptText->GetText().ToString());
}

void UAIM_WelcomeWidget::OnTextChanged(const FText& Text)
{
    CreateButton->SetIsEnabled(!Text.ToString().IsEmpty());
}

void UAIM_WelcomeWidget::Show()
{
    PromptText->SetFocus();
}

void UAIM_WelcomeWidget::SetError(const FString& Error)
{
    ErrorMessage->SetText(FText::FromString(Error));
    ErrorMessage->SetVisibility(Error.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}
