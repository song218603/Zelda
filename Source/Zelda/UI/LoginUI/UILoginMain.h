// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/UIBase.h"
#include "Network/NetCode/NetCode.h"
#include "UILoginMain.generated.h"

class UMediaPlayer;
class UMediaSource;
class ULoginPopup;


UCLASS()
class ZELDA_API UUILoginMain : public UUIBase
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* LoginCanvas;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginBtn;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RegisterBtn;
	
	UPROPERTY(meta = (BindWidget))
	class UEditableText* UsernameInput;

	// 绑定密码输入框
	UPROPERTY(meta = (BindWidget))
	class UEditableText* PasswordInput;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zelda|Login|BGVideo")
	UMediaPlayer* BGMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zelda|Login|BGVideo")
	UMediaSource* BGMediaSource;
	
	UPROPERTY(EditAnywhere, Category = "Zelda|Login|Popup")
	TSubclassOf<ULoginPopup> PopupClass;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnLoginClicked();
	
	UFUNCTION()
	void OnRegisterClicked();
	
	void PopupTip(FString Message);
	
private:
	bool CheckAccount() const;
	
	UFUNCTION()
	void HandleLoginResult(ELoginResult Result);
};
