// Zelda Games


#include "LoginPopup.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULoginPopup::SetPopupMessage(FText InMessage)
{
	if (TipText)
	{
		TipText->SetText(InMessage);
	}
}

void ULoginPopup::NativeConstruct()
{
	Super::NativeConstruct();
	if (ConfirmBtn)
	{
		ConfirmBtn->OnClicked.AddDynamic(this, &ThisClass::OnConfirmClicked);
	}
}

void ULoginPopup::OnConfirmClicked()
{
	RemoveFromParent();
}
