// Zelda Games


#include "AnimNotify_AnimSignal.h"
#include "Combat/Interface/CombatInterface.h"

UAnimNotify_AnimSignal::UAnimNotify_AnimSignal() : Signal(INDEX_NONE)
{
}

void UAnimNotify_AnimSignal::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOuter()))
	{
		CombatInterface->AnimSignal(Signal);
	}
}

FString UAnimNotify_AnimSignal::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
