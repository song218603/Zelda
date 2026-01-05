// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/UIBase.h"
#include "UI_LobbyMain.generated.h"



UCLASS()
class ZELDA_API UUI_LobbyMain : public UUIBase
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameBtn;
	
public:
	virtual void NativeConstruct() override;
	
	void JumpDSServer() const;
	
	UFUNCTION()
	void OnStartGameClicked();
};
