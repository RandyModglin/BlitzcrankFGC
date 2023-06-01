// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlitzcrankFGCCharacter.h"
#include "Dummy.h"
#include "BlitzcrankFGCGameMode.generated.h"

UCLASS(minimalapi)
class ABlitzcrankFGCGameMode : public AGameModeBase
{
	GENERATED_BODY()


	ADummy* getDummy();

public:
	ABlitzcrankFGCGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ABlitzcrankFGCCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ADummy* Dummy;
};



