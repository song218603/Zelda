// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/IHttpRequest.h"
#include "Network/NetCode/NetCode.h"
#include "ZeldaGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginFinished, ELoginResult, Result);

UCLASS()
class ZELDA_API UZeldaGameInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override;
	
	virtual void Shutdown() override;
	
	UFUNCTION(BlueprintCallable, Category = "Zelda|Network")
	void Login(FString Username, FString Password);
	
	// 登录结果委托
	UPROPERTY(BlueprintAssignable, Category = "Zelda|Network")
	FOnLoginFinished OnLoginFinished;

	
private:
	void OnLoginResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	// 心跳函数
	void SendHeartbeat() const;
	FTimerHandle HeartbeatTimerHandle;
	FString Username;
	uint32 Health;
	uint32 Energy;
};
