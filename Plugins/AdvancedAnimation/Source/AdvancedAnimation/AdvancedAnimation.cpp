// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedAnimation.h"
#include "Core/AdvancedAnimSystem.h"

#define LOCTEXT_NAMESPACE "FAdvancedAnimationModule"

void FAdvancedAnimationModule::StartupModule()
{
	
}

void FAdvancedAnimationModule::ShutdownModule()
{
	FAdvancedAnimSystem::Get()->Destroy();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdvancedAnimationModule, AdvancedAnimation)