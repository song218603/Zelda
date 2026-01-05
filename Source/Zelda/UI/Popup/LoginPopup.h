// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/UIBase.h"
#include "LoginPopup.generated.h"


UCLASS()
class ZELDA_API ULoginPopup : public UUIBase
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmBtn;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TipText;
	
public:
	
	void SetPopupMessage(FText InMessage);
	
protected:
	virtual void NativeConstruct() override;
	
	// 按钮点击的回调函数
	UFUNCTION()
	void OnConfirmClicked();
};
