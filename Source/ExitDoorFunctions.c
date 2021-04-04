/******************************************************************************
filename    ExitDoorFunctions.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "exit door".

******************************************************************************/
#include "stdafx.h" /* NULL, UNREFERENCED_PARAMETER */
#include <stdio.h>
#include "ExitDoorFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_EndGame */
#include "ItemList.h" /* ItemList_FindItem */
#include "Item.h" /* Item_Create */
#include "Room.h"
#include "RoomExit.h"
#include "WorldData.h"
#include <ctype.h>
typedef struct WorldData WorldData;

#define MAX_LIMIT 9 

/* Helper: The action performed when the exit door is used. */
void ExitDoor_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room;
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	printf("A voice rumbles in your mind. \"To continue to the foyer, you must provide the unforgettable password\"\nWhat is the password? ");
	
	char str[9];
	fgets(str, 9, stdin);
	for (int i = 0; i < 9; i++)
		str[i] = (char) tolower(str[i]);
	if (strcmp(str, "madeline") == 0)
	{
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
		printf("After speaking the password, the large door opens. You may now move north.");
		Room_AddRoomExit(room, "north", 8);
	}
}


/* Build a "exit door" object */
Item* ExitDoor_Build()
{
	/* Create a "exit door" item, using the functions defined in this file */
	return Item_Create("exit door", "a large door with no visible lock, doorknob, or keyhole.\n", false, ExitDoor_Use, NULL, NULL);
}