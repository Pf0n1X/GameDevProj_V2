// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameDevProj_V2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVPROJ_V2_API AGameDevProj_V2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
