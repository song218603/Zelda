// Zelda Games


#include "UILoginMain.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableText.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "UI/Popup/LoginPopup.h"
#include "GameBase/GameInstance/ZeldaGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UUILoginMain::NativeConstruct()
{
	Super::NativeConstruct();
	if (LoginBtn)
	{
		// 绑定按钮点击事件
		LoginBtn->OnClicked.AddDynamic(this, &ThisClass::OnLoginClicked);
	}
	if (UZeldaGameInstance* GI = GetGameInstance<UZeldaGameInstance>())
	{
		// 绑定回调函数
		GI->OnLoginFinished.AddDynamic(this, &ThisClass::HandleLoginResult);
	}
	if (RegisterBtn)
	{
		RegisterBtn->OnClicked.AddDynamic(this, &ThisClass::OnRegisterClicked);
	}
	
	if (BGMediaPlayer && BGMediaSource)
	{
		// 设置循环播放
		BGMediaPlayer->SetLooping(true);
		// 打开并播放视频
		if (BGMediaPlayer->OpenSource(BGMediaSource))
		{
			// 显式调用播放
			BGMediaPlayer->Play();
		}
	}
}

void UUILoginMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUILoginMain::OnLoginClicked()
{
	// 获取输入框的文本内容
	if (!CheckAccount())
	{
		PopupTip(TEXT("Please Input Correct Username and Password."));
		return;
	}
	
	UZeldaGameInstance* GI = GetGameInstance<UZeldaGameInstance>();
	if (!GI)
	{
		PopupTip(TEXT("Unknown Error."));
		return;
	}
	
	GI->Login(UsernameInput->GetText().ToString(), PasswordInput->GetText().ToString());
}

void UUILoginMain::OnRegisterClicked()
{
	PopupTip(TEXT("Can`t Register Now."));
}

void UUILoginMain::PopupTip(FString Message)
{
	if (PopupClass)
	{
		ULoginPopup* NewPopup = CreateWidget<ULoginPopup>(this, PopupClass);
        
		if (NewPopup)
		{
			NewPopup->SetPopupMessage(FText::FromString(Message));
			NewPopup->AddToViewport(100);
		}
	}
}

bool UUILoginMain::CheckAccount() const
{
	if (UsernameInput && PasswordInput)
	{
		if (UsernameInput->GetText().IsEmpty() || PasswordInput->GetText().IsEmpty()) return false;
		return true;
	}
	return false;
}

void UUILoginMain::HandleLoginResult(ELoginResult Result)
{
	switch (Result)
	{
	case ELoginResult::Success:
		if (LoginCanvas)
			LoginCanvas->SetVisibility(ESlateVisibility::Collapsed);
		LoginBtn->SetIsEnabled(false);
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Lobby"));
		break;
	case ELoginResult::NetworkError:
		PopupTip(TEXT("Network Error."));
		break;
	default:
		PopupTip(TEXT("Username or Password Error."));
	}
	
}
