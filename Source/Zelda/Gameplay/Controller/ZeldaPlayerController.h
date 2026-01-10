// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZeldaPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;


UCLASS(abstract)
class AZeldaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category ="Zelda|Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category="Zelda|Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	UPROPERTY(EditAnywhere, Category="Zelda|Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	UPROPERTY(EditAnywhere, Config, Category = "Zelda|Input|Touch Controls")
	bool bForceTouchControls = false;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	bool ShouldUseTouchControls() const;

};
