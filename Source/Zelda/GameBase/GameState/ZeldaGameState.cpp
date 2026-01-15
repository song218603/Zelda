// Zelda Games


#include "ZeldaGameState.h"

AZeldaGameState::AZeldaGameState()
{
	// 注册数据表
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimDataTable(TEXT("/Game/ZeldaGame/GameAbility/DataTable/DT_ZeldaCharacterAnimDataTable"));
}

