// Zelda Games


#include "LobbyGameMode.h"

#include "GameBase/HUD/Lobby/LobbyHUD.h"
#include "Gameplay/Controller/Lobby/LobbyPlayerController.h"
#include "Gameplay/Pawn/Lobby/LobbyPawn.h"

ALobbyGameMode::ALobbyGameMode()
{
	HUDClass = ALobbyHUD::StaticClass();
	DefaultPawnClass = ALobbyPawn::StaticClass();
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
}
