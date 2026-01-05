// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Lobby/UI_LobbyMain.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZELDA_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	TSubclassOf<UUI_LobbyMain> LobbyMainClass;	// 通过蓝图获得 LobbyUI
	
public:
	ALobbyHUD();
	virtual void BeginPlay() override;
	
private:
	UUI_LobbyMain* LobbyMain;
};
