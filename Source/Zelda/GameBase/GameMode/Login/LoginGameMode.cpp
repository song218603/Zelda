// Zelda Games


#include "LoginGameMode.h"
#include "GameBase/HUD/Login/LoginHUD.h"
#include "Player/Pawn/Login/LoginPawn.h"
#include "Player/Controller/Login/LoginPlayerController.h"

ALoginGameMode::ALoginGameMode()
{
	HUDClass = ALoginHUD::StaticClass();
	DefaultPawnClass = ALoginPawn::StaticClass();
	PlayerControllerClass = ALoginPlayerController::StaticClass();
}
