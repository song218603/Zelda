// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"



UCLASS()
class ZELDA_API UUIBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	template <class T>
	T* GetPlayerController()
	{
		return GetWorld() != nullptr ? GetWorld()->GetFirstPlayerController<T>() : nullptr;
	}
	
	template <class T>
	T* GetPawn()
	{
		return GetWorld() != nullptr ? 
		(GetWorld()->GetFirstPlayerController() != nullptr ? GetWorld()->GetFirstPlayerController()->GetPawn<T>() : nullptr) 
		: nullptr;
	}
	
	template<class T>
	T* GetGameInstance()
	{
		// 只能在客户端使用
		return GetWorld() != nullptr ? GetWorld()->GetGameInstance<T>() : nullptr;
	}
};
