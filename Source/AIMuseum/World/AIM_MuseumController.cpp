// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "World/AIM_MuseumController.h"
#include "World/AIM_Art.h"
#include "Kismet/GameplayStatics.h"
#include "Provider/OpenAIProvider.h"
#include "FuncLib/OpenAIFuncLib.h"
#include "FuncLib/ImageFuncLib.h"
#include "World/AIM_ExitPortal.h"
#include "GameFramework/PlayerStart.h"
#include "UI/AIM_MainWidget.h"
#include "UI/AIM_ViewModel.h"
#include "Algo/ForEach.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogMuseumController, All, All);

namespace
{
constexpr int32 MaxNumOfImages = 10;

int32 ClampImageAmount(int32 RequestedNum)
{
    return FMath::Clamp(RequestedNum, 1, MaxNumOfImages);
}

void SetUIInput(UWorld* World, bool Enabled)
{
    if (!World) return;
    if (auto* PC = World->GetFirstPlayerController())
    {
        PC->SetShowMouseCursor(Enabled);
        Enabled ? PC->SetInputMode(FInputModeUIOnly()) : PC->SetInputMode(FInputModeGameOnly());
    }
}

}  // namespace

void AAIM_MuseumController::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> ArtActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIM_Art::StaticClass(), ArtActors);
    for (auto* ArtActor : ArtActors)
    {
        if (auto* Art = Cast<AAIM_Art>(ArtActor))
        {
            Arts.Add(Art);
        }
    }

    // OpenAI

    Auth = UOpenAIFuncLib::LoadAPITokensFromFile(FPaths::ProjectDir().Append("OpenAIAuth.ini"));

    Provider = NewObject<UOpenAIProvider>();
    check(Provider);
    Provider->SetLogEnabled(true);
    Provider->OnCreateImageCompleted().AddUObject(this, &ThisClass::OnCreateImageCompleted);

    Provider->OnCreateChatCompletionCompleted().AddLambda(
        [&](const FChatCompletionResponse& Response)
        {
            FString OutputMessage;
            Algo::ForEach(Response.Choices, [&](const FChatChoice& Choice) {  //
                OutputMessage.Append(Choice.Message.Content);
            });

            MuseumViewModel->SetPrompt(FText::FromString(OutputMessage));
            MuseumViewModel->SetRandInProgress(false);

            FMessage Message;
            Message.Content = OutputMessage;
            Message.Role = UOpenAIFuncLib::OpenAIRoleToString(ERole::Assistant);
            ChatHistory.Add(Message);

            Message.Content = "Another one, all the words are different. Don't repeat words from the history.";
            Message.Role = UOpenAIFuncLib::OpenAIRoleToString(ERole::User);
            ChatHistory.Add(Message);
        });

    Provider->OnRequestError().AddUObject(this, &ThisClass::OnRequestError);

    FMessage Message;
    Message.Content = "Generate funny 2-3 word description for image generation for dalle3. Output without additional text, without "
                      "quotes, without lists, just 2-3 words the whole sentence, only one variant.";
    Message.Role = UOpenAIFuncLib::OpenAIRoleToString(ERole::User);
    ChatHistory.Add(Message);

    check(ExitPortal);
    ExitPortal->OnExitExperience().AddUObject(this, &ThisClass::OnExitExperience);

    check(PlayerStart);

    // UI
    MainWidget = CreateWidget<UAIM_MainWidget>(GetWorld(), MainWidgetClass);
    check(MainWidget);
    MainWidget->AddToViewport();
    MainWidget->OnStartExperience().BindUObject(this, &ThisClass::OnStartExperience);
    MainWidget->OnRandomRequested().BindUObject(this, &ThisClass::OnPromptRandomize);

    // View Model
    MuseumViewModel = NewObject<UAIM_ViewModel>();
    check(MuseumViewModel);
    MainWidget->SetViewModel(MuseumViewModel);

    ShowWelcomeWidget();
}

void AAIM_MuseumController::OnStartExperience()
{
    if (!bImageGenerationEnabled) return;

    ArtTextures.Empty();

    const auto ImageModel = MuseumViewModel->GetImageModel();
    ImageRequestData.TotalCount = ClampImageAmount(ImageAmount[ImageModel]);
    ImageRequestData.DownloadedCount = 0;

    RequestImages();
}

void AAIM_MuseumController::OnPromptRandomize()
{
    FChatCompletion ChatCompletion;
    ChatCompletion.Model = UOpenAIFuncLib::OpenAIMainModelToString(EMainModelEnum::GPT_4O);
    ChatCompletion.Max_Tokens = 100;
    ChatCompletion.Stream = false;
    ChatCompletion.Messages = ChatHistory;
    ChatCompletion.Seed = FMath::RandRange(0.0, 10.0);

    MuseumViewModel->SetRandInProgress(true);
    Provider->CreateChatCompletion(ChatCompletion, Auth);
}

void AAIM_MuseumController::RequestImages()
{
    switch (MuseumViewModel->GetImageModel())
    {
        case EImageModelEnum::DALL_E_2: MakeDalle2Request(); break;
        case EImageModelEnum::DALL_E_3: MakeDalle3Request(); break;

        default: checkNoEntry(); break;
    }
}

void AAIM_MuseumController::MakeDalle2Request()
{
    FOpenAIImage Image;
    Image.Prompt = MuseumViewModel->GetPrompt().ToString();
    Image.Size = UOpenAIFuncLib::OpenAIImageSizeDalle2ToString(EImageSizeDalle2::Size_512x512);
    Image.Response_Format = UOpenAIFuncLib::OpenAIImageFormatToString(ImageFormat);
    Image.Model = UOpenAIFuncLib::OpenAIImageModelToString(EImageModelEnum::DALL_E_2);
    Image.N = FMath::Min(Arts.Num(), ClampImageAmount(ImageAmount[EImageModelEnum::DALL_E_2]));
    ImageRequestData.NumPerRequest = Image.N;

    Provider->CreateImage(Image, Auth);
}

void AAIM_MuseumController::MakeDalle3Request()
{
    FOpenAIImage Image;
    Image.Prompt = MuseumViewModel->GetPrompt().ToString();
    Image.Size = UOpenAIFuncLib::OpenAIImageSizeDalle3ToString(EImageSizeDalle3::Size_1024x1024);
    Image.Response_Format = UOpenAIFuncLib::OpenAIImageFormatToString(ImageFormat);
    Image.Model = UOpenAIFuncLib::OpenAIImageModelToString(EImageModelEnum::DALL_E_3);
    Image.N = 1;
    ImageRequestData.NumPerRequest = Image.N;
    Provider->CreateImage(Image, Auth);

    UAIM_ViewModel::FImageLoadingProgress ImageLoadingProgress;
    ImageLoadingProgress.CurrentNum = ArtTextures.Num() + 1;
    ImageLoadingProgress.Count = ClampImageAmount(ImageAmount[EImageModelEnum::DALL_E_3]);
    MuseumViewModel->SetImageLoadingProgress(ImageLoadingProgress);
}

void AAIM_MuseumController::OnCreateImageCompleted(const FImageResponse& Response)
{
    if (Response.Data.Num() < 1)
    {
        ShowError("No images were generated");
        return;
    }

    check(ImageRequestData.NumPerRequest == Response.Data.Num());

    for (const auto& ImageObject : Response.Data)
    {
        switch (ImageFormat)
        {
            case EOpenAIImageFormat::URL: DownloadImage(ImageObject.URL); break;
            case EOpenAIImageFormat::B64_JSON:
            {
                auto* ArtTexture = UImageFuncLib::Texture2DFromBytes(ImageObject.B64_JSON);
                ArtTextures.Add(ArtTexture);
                break;
            }
            default: checkNoEntry(); break;
        }
    }

    if (ImageFormat == EOpenAIImageFormat::B64_JSON)
    {
        ImageRequestData.TotalCount == ArtTextures.Num() ? StartMuseumWalking() : RequestImages();
    }
}

void AAIM_MuseumController::DownloadImage(const FString& URL)
{
    auto HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnImageDownloaded);
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb(TEXT("GET"));
    HttpRequest->ProcessRequest();
}

void AAIM_MuseumController::OnImageDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
{
    if (!bSucceeded || !Response)
    {
        ShowError("Image downloading error.");
        return;
    }

    auto* ArtTexture = UImageFuncLib::CreateTexture(Response->GetContent());
    ArtTextures.Add(ArtTexture);
    ImageRequestData.DownloadedCount += 1;

    if (ImageRequestData.TotalCount == ArtTextures.Num())
    {
        StartMuseumWalking();
    }
    else if (ImageRequestData.DownloadedCount == ImageRequestData.NumPerRequest)
    {
        RequestImages();
    }
}

void AAIM_MuseumController::UpdateTextures()
{
    int32 Index = 0;
    for (auto* Art : Arts)
    {
        Art->SetArtTexture(ArtTextures[Index]);
        Index = (Index + 1) % ArtTextures.Num();
    }
}

void AAIM_MuseumController::StartMuseumWalking()
{
    UpdateTextures();
    MainWidget->HideAll();
    SetUIInput(GetWorld(), false);
}

void AAIM_MuseumController::OnRequestError(const FString& URL, const FString& Content)
{
    const FString Message = UOpenAIFuncLib::GetErrorMessage(Content);
    const FString ErrorMessage = FString::Format(TEXT("URL:{0}, Message:{1}"), {URL, Message});
    ShowError(ErrorMessage);
}

void AAIM_MuseumController::ShowError(const FString& ErrorMessage)
{
    UE_LOGFMT(LogMuseumController, Error, "{0}", ErrorMessage);

    MuseumViewModel->SetErrorMessage(FText::FromString(ErrorMessage));
    MuseumViewModel->SetRandInProgress(false);

    static constexpr float HideSeconds = 5.0f;
    static FTimerHandle ErrorTimerHandle;
    GetWorldTimerManager().SetTimer(
        ErrorTimerHandle, [this]() { MuseumViewModel->SetErrorMessage(FText{}); }, HideSeconds, false);

    ShowWelcomeWidget();
}

void AAIM_MuseumController::OnExitExperience()
{
    if (!GetWorld() || !PlayerStart) return;

    if (auto* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->SetControlRotation(PlayerStart->GetActorRotation());
        if (auto* Pawn = PC->GetPawn())
        {
            Pawn->TeleportTo(PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
            // RequestImages(GeneratePrompt(), Arts.Num());
            ShowWelcomeWidget();
        }
    }
}

void AAIM_MuseumController::ShowWelcomeWidget()
{
    MainWidget->Show(EAIMuseumUIState::Welcome);
    SetUIInput(GetWorld(), true);
}

FString AAIM_MuseumController::GeneratePrompt() const
{
    const TArray<FString> Prompts = {"Kitten playing metal on guitars",        //
        "Photorealistic Godzilla meets cartoon cat Tom (from Tom and Jerry)",  //
        "Photorealistic flying whale in the clouds"};

    static int32 Index = -1;
    Index = (Index + 1) % Prompts.Num();

    return Prompts[Index];
}
