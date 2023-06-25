// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlitzcrankFGCGameMode.h"
#include "BlitzcrankFGCCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlitzcrankFGCGameMode::ABlitzcrankFGCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Player = nullptr;
	Dummy = nullptr;
}

ADummy* ABlitzcrankFGCGameMode::getDummy() {
	return Dummy;
}
