// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "World/AIM_MuseumController.h"
#include "World/AIM_Art.h"
#include "Kismet/GameplayStatics.h"
#include "Provider/OpenAIProvider.h"
#include "FuncLib/OpenAIFuncLib.h"
#include "FuncLib/ImageFuncLib.h"
#include "World/AIM_ExitPortal.h"
#include "GameFramework/PlayerStart.h"
#include "UI/MainWidget.h"
#include "UI/Model/VMAIMuseum.h"

DEFINE_LOG_CATEGORY_STATIC(LogMuseumController, All, All);

namespace
{
constexpr int32 MaxNumOfImages = 10;

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

    Auth = UOpenAIFuncLib::LoadAPITokensFromFile(FPaths::ProjectDir().Append("OpenAIAuth.ini"));

    Provider = NewObject<UOpenAIProvider>();
    check(Provider);
    Provider->SetLogEnabled(true);
    Provider->OnCreateImageCompleted().AddUObject(this, &ThisClass::OnCreateImageCompleted);
    Provider->OnRequestError().AddUObject(this, &ThisClass::OnRequestError);

    check(ExitPortal);
    ExitPortal->OnExitExperience().AddUObject(this, &ThisClass::OnExitExperience);

    check(PlayerStart);

    // UI
    MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
    check(MainWidget);
    MainWidget->AddToViewport();
    MainWidget->OnStartExperience().AddDynamic(this, &ThisClass::OnStartExperience);

    // UI model
    VMAIMuseum = NewObject<UVMAIMuseum>();
    check(VMAIMuseum);
    MainWidget->SetModel(VMAIMuseum);

    ShowWelcomeWidget();
}

void AAIM_MuseumController::RequestImages(const FString& Prompt, int32 NumOfImages)
{
    if (!bImageGenerationEnabled) return;

    FOpenAIImage Image;
    Image.Prompt = Prompt;
    Image.Size = UOpenAIFuncLib::OpenAIImageSizeDalle2ToString(EImageSizeDalle2::Size_512x512);
    Image.Response_Format = UOpenAIFuncLib::OpenAIImageFormatToString(EOpenAIImageFormat::B64_JSON);
    Image.N = 11;  //  FMath::Min(NumOfImages, MaxNumOfImages);

    Provider->CreateImage(Image, Auth);
}

void AAIM_MuseumController::OnCreateImageCompleted(const FImageResponse& Response)
{
    if (Response.Data.Num() < 1)
    {
        UE_LOG(LogMuseumController, Warning, TEXT("No images were generated"));
        ShowWelcomeWidget();
        return;
    }

    int32 Index = 0;
    for (auto* Art : Arts)
    {
        auto* ArtTexture = UImageFuncLib::Texture2DFromBytes(Response.Data[Index].B64_JSON);
        Art->SetArtTexture(ArtTexture);
        Index = (Index + 1) % Response.Data.Num();
    }

    MainWidget->HideAll();
    SetUIInput(GetWorld(), false);
}

void AAIM_MuseumController::OnRequestError(const FString& URL, const FString& Content)
{
    const FString Message = UOpenAIFuncLib::GetErrorMessage(Content);
    const FString OutputMessage = FString::Format(TEXT("URL:{0}, Message:{1}"), {URL, Message});
    UE_LOG(LogMuseumController, Error, TEXT("%s"), *OutputMessage);

    VMAIMuseum->SetError(FText::FromString(OutputMessage));
    constexpr float HideSeconds = 3.0f;

    static FTimerHandle ErrorShowingTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        ErrorShowingTimerHandle, [this]() { VMAIMuseum->SetError(FText::FromString("")); }, HideSeconds, false);

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
            ShowWelcomeWidget();
        }
    }
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

void AAIM_MuseumController::OnStartExperience()
{
    RequestImages(VMAIMuseum->GetPrompt().ToString(), Arts.Num());
}

void AAIM_MuseumController::ShowWelcomeWidget()
{
    SetUIInput(GetWorld(), true);
    MainWidget->Show(EAIMuseumUIState::Welcome);
}
