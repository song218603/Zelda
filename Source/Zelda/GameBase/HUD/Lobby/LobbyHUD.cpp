// Zelda Games


#include "LobbyHUD.h"

ALobbyHUD::ALobbyHUD()
{
	// 获取 Login UI 蓝图类
	static ConstructorHelpers::FClassFinder<UUI_LobbyMain> LobbyMain_BP(TEXT("/Game/ZeldaGame/UI/Lobby/WBP_LobbyMain"));
	LobbyMainClass = LobbyMain_BP.Class;
}

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (LobbyMainClass)
	{
		LobbyMain = CreateWidget<UUI_LobbyMain>(GetWorld(), LobbyMainClass);
		LobbyMain->AddToViewport();
	}
}
