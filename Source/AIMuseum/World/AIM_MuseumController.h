// AI Museum, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Provider/CommonTypes.h"
#include "HTTP.h"
#include "FuncLib/ModelTypes.h"
#include "AIM_MuseumController.generated.h"

class AAIM_Art;
class UOpenAIProvider;
struct FImageResponse;
class AAIM_ExitPortal;
class APlayerStart;
class UAIM_MainWidget;
class UAIM_ViewModel;

UCLASS()
class AIMUSEUM_API AAIM_MuseumController : public AInfo
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<AAIM_ExitPortal> ExitPortal;

    UPROPERTY(EditAnywhere)
    TObjectPtr<APlayerStart> PlayerStart;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UAIM_MainWidget> MainWidgetClass;

    UPROPERTY(EditAnywhere)
    bool bImageGenerationEnabled{true};

    UPROPERTY(EditAnywhere)
    TMap<EImageModelEnum, int32> ImageAmount{//
        {EImageModelEnum::DALL_E_2, 10}, {EImageModelEnum::DALL_E_3, 3}};

    UPROPERTY(EditAnywhere)
    EOpenAIImageFormat ImageFormat{EOpenAIImageFormat::B64_JSON};

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<AAIM_Art*> Arts;

    UPROPERTY()
    TObjectPtr<UOpenAIProvider> Provider;

    UPROPERTY()
    TObjectPtr<UAIM_MainWidget> MainWidget;

    UPROPERTY()
    TObjectPtr<UAIM_ViewModel> MuseumViewModel;

    UPROPERTY()
    TArray<TObjectPtr<UTexture2D>> ArtTextures;

    FOpenAIAuth Auth;
    TArray<FMessage> ChatHistory;

    struct FImageRequestData
    {
        int32 TotalCount;
        int32 NumPerRequest;
        int32 DownloadedCount;
    } ImageRequestData;

    void RequestImages();
    void MakeDalle2Request();
    void MakeDalle3Request();
    void DownloadImage(const FString& URL);
    void OnImageDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded);
    void UpdateTextures();
    void StartMuseumWalking();

    void OnCreateImageCompleted(const FImageResponse& Response);
    void OnRequestError(const FString& URL, const FString& Content);
    void ShowError(const FString& ErrorMessage);

    void OnStartExperience();
    void OnExitExperience();
    void OnPromptRandomize();

    void ShowWelcomeWidget();

    FString GeneratePrompt() const;
};
