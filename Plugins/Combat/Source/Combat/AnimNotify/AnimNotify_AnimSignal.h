// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AnimSignal.generated.h"


UCLASS()
class COMBAT_API UAnimNotify_AnimSignal : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_AnimSignal();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatPlugin|AnimNotify")
	int32 Signal;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;
};
