// AI Museum, Copyright LifeEXE. All Rights Reserved.

#include "World/AIM_MuseumController.h"
#include "World/AIM_Art.h"
#include "Kismet/GameplayStatics.h"
#include "Provider/OpenAIProvider.h"
#include "FuncLib/OpenAIFuncLib.h"
#include "FuncLib/ImageFuncLib.h"

DEFINE_LOG_CATEGORY_STATIC(LogMuseumController, All, All);

namespace
{
constexpr int32 MaxNumOfImages = 10;
}

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

    const FString Prompt = "Kitten playing metal on guitars";
    RequestImages(Prompt, Arts.Num());
}

void AAIM_MuseumController::RequestImages(const FString& Prompt, int32 NumOfImages)
{
    FOpenAIImage Image;
    Image.Prompt = Prompt;
    Image.Size = UOpenAIFuncLib::OpenAIImageSizeToString(EImageSize::Size_512x512);
    Image.Response_Format = UOpenAIFuncLib::OpenAIImageFormatToString(EOpenAIImageFormat::B64_JSON);
    Image.N = FMath::Min(NumOfImages, MaxNumOfImages);

    Provider->CreateImage(Image, Auth);
}

void AAIM_MuseumController::OnCreateImageCompleted(const FImageResponse& Response)
{

    if (Response.Data.Num() < 1)
    {
        UE_LOG(LogMuseumController, Warning, TEXT("No images were generated"));
        return;
    }

    int32 Index = 0;
    for (auto* Art : Arts)
    {
        auto* ArtTexture = UImageFuncLib::Texture2DFromBytes(Response.Data[Index]);
        Art->SetArtTexture(ArtTexture);
        Index = (Index + 1) % Response.Data.Num();
    }
}

void AAIM_MuseumController::OnRequestError(const FString& URL, const FString& Content)
{
    const FString Message = UOpenAIFuncLib::GetErrorMessage(Content);
    const FString OutputMessage = FString::Format(TEXT("URL:{0}, Message:{1}"), {URL, Message});
    UE_LOG(LogMuseumController, Error, TEXT("%s"), *OutputMessage);
}
