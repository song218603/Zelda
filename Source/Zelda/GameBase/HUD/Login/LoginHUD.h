// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/LoginUI/UILoginMain.h"
#include "LoginHUD.generated.h"



UCLASS()
class ZELDA_API ALoginHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	TSubclassOf<UUILoginMain> LoginMainClass;	// 通过蓝图获得 LoginUI
	
public:
	ALoginHUD();
	
	virtual void BeginPlay() override;
	
private:
	UUILoginMain* LoginMain;
};
