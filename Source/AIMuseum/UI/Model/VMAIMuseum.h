// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VMAIMuseum.generated.h"

UCLASS()
class AIMUSEUM_API UVMAIMuseum : public UMVVMViewModelBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    FText Prompt{};

private:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    FText Error{};

public:
    void SetPrompt(const FText& NewPrompt)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(Prompt, NewPrompt))
        {
            UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsPromptEmpty);
        }
    }
    FText GetPrompt() const { return Prompt; }

    void SetError(const FText& NewError)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(Error, NewError))
        {
            UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsErrorVisible);
        }
    }
    FText GetError() const { return Error; }

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsErrorVisible() const { return !Error.IsEmpty(); }

    UFUNCTION(BlueprintPure, FieldNotify)
    bool IsPromptEmpty() const { return Prompt.IsEmpty(); }

};
