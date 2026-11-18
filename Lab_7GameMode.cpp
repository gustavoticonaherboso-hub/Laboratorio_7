// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab_7GameMode.h"
#include "Lab_7Pawn.h"

ALab_7GameMode::ALab_7GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ALab_7Pawn::StaticClass();
}

