// Zelda Games


#include "ZeldaGameMode.h"
#include "GameBase/GameState/ZeldaGameState.h"
#include "GameBase/HUD/Game/GameHUD.h"
#include "GameBase/PlayerState/ZeldaPlayerState.h"
#include "Gameplay/Controller/ZeldaPlayerController.h"

AZeldaGameMode::AZeldaGameMode()
{
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AZeldaPlayerState::StaticClass();
	GameStateClass = AZeldaGameState::StaticClass();
	PlayerControllerClass = AZeldaPlayerController::StaticClass();
	GameStateClass = AZeldaGameState::StaticClass();
	PlayerStateClass = AZeldaPlayerState::StaticClass();
}
