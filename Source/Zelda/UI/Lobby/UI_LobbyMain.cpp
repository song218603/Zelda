// Zelda Games


#include "UI_LobbyMain.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUI_LobbyMain::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (StartGameBtn)
	{
		// 绑定按钮点击事件
		StartGameBtn->OnClicked.AddDynamic(this, &ThisClass::OnStartGameClicked);
	}
}

void UUI_LobbyMain::JumpDSServer() const
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Hyrule/Hyrule"));
}

void UUI_LobbyMain::OnStartGameClicked()
{
	JumpDSServer();
}
