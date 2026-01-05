// Zelda Games


#include "LoginHUD.h"

ALoginHUD::ALoginHUD()
{
	// 获取 Login UI 蓝图类
	static ConstructorHelpers::FClassFinder<UUILoginMain> LoginMain_BP(TEXT("/Game/ZeldaGame/UI/Login/WBP_LoginMain"));
	LoginMainClass = LoginMain_BP.Class;
}

void ALoginHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (LoginMainClass)
	{
		LoginMain = CreateWidget<UUILoginMain>(GetWorld(), LoginMainClass);
		LoginMain->AddToViewport();
	}
}
