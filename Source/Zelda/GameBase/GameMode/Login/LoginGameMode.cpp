// Zelda Games


#include "LoginGameMode.h"
#include "GameBase/HUD/Login/LoginHUD.h"
#include "Gameplay/Pawn/Login/LoginPawn.h"
#include "Gameplay/Controller/Login/LoginPlayerController.h"

ALoginGameMode::ALoginGameMode()
{
	HUDClass = ALoginHUD::StaticClass();
	DefaultPawnClass = ALoginPawn::StaticClass();
	PlayerControllerClass = ALoginPlayerController::StaticClass();
}
