// Zelda Games


#include "LobbyGameMode.h"

#include "GameBase/HUD/Lobby/LobbyHUD.h"
#include "Player/Controller/Lobby/LobbyPlayerController.h"
#include "Player/Pawn/Lobby/LobbyPawn.h"

ALobbyGameMode::ALobbyGameMode()
{
	HUDClass = ALobbyHUD::StaticClass();
	DefaultPawnClass = ALobbyPawn::StaticClass();
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
}
