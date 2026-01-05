// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "NetCode.generated.h"


UENUM(BlueprintType)
enum class ELoginResult : uint8
{
	Success			UMETA(DisplayName = "成功"),
	WrongPass		UMETA(DisplayName = "密码错误"),
	NoUser			UMETA(DisplayName = "账号不存在"),
	NetworkError	UMETA(DisplayName = "网络错误")
};
