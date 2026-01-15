// Zelda Games

#pragma once

#include "CoreMinimal.h"


namespace Utils
{
	enum class EServerCallType : uint8
	{
		INPROGRESS,
		PROGRESS_COMPLETED
	};
	
	template<class T>
	void ServerCallAllPlayerController(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		for (FConstPlayerControllerIterator It = NewWorld->GetPlayerControllerIterator(); It; ++It)
		{
			if (T* InPlayerController = Cast<T>(It->Get()))
			{
				if (InImplement(InPlayerController) == EServerCallType::PROGRESS_COMPLETED)
				{
					break;
				}
			}
		}
	}
	
	template<class T>
	void ServerCallAllPlayer(UWorld* NewWorld, TFunction<EServerCallType(T*)> InImplement)
	{
		ServerCallAllPlayerController<APlayerController>(NewWorld, [&](APlayerController* InPlayerController) -> EServerCallType
		{
			if (T* InPawn = Cast<T>(InPlayerController->GetPawn()))
			{
				return InImplement(InPawn);
			}
			return EServerCallType::PROGRESS_COMPLETED;
		});
	}
}
