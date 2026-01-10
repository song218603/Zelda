// Zelda Games


#include "ZeldaGameState.h"

AZeldaGameState::AZeldaGameState()
{
	// 注册数据表
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimDataTable(TEXT("/Game/ZeldaGAme/GameAbility/DataTable/DT_ZeldaCharacterAnimDataTable"));
	CharacterAnimDataTablePtr = CharacterAnimDataTable.Object;
}

FZeldaCharacterAnimTable* AZeldaGameState::GetAnimTable(uint32 AnimID)
{
	
	return *GetAnimTables().FindByPredicate([&](FZeldaCharacterAnimTable* AnimTable)
	{
		return AnimTable->ID ==  AnimID;
	});
}

TArray<FZeldaCharacterAnimTable*> AZeldaGameState::GetAnimTables()
{
	if (!CharacterAnimDataTables.Num())
	{
		if (CharacterAnimDataTablePtr)
			CharacterAnimDataTablePtr->GetAllRows(TEXT("AnimTable"), CharacterAnimDataTables);
	}
	return CharacterAnimDataTables;
}
