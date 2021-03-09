/******************************************************************************
filename    BrickFunctions.c
author      Thomas Allen
DP email    thomas.allen@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "brick".

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "RustedKeyFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */

void Sword_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the brick might be used, whenever it is picked up. */
	printf("The sword is old and shimmers like moonlight. It feels well balanced in your hand.\n");
}

void Sword_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	Item* sword;

	UNREFERENCED_PARAMETER(context);
	
	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}


	if (GameFlags_IsInList(gameState->gameFlags, "room3GhostDead"))
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("There are no ghosts to slay!\n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 3)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the sword here.\n");
		return;
	}
	else
	{
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
		sword = ItemList_FindItem(gameState->inventory, "sword");
		gameState->inventory = ItemList_Remove(gameState->inventory, sword);

		printf("You draw the sword and slash across the ghost's etheral body. It releases one last screech until it fades away into nothingness. Quickly, however, the sword follows suit!\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 3.  The room is strangly eerie without the screech of the ghost, though you think there may be more chasing you now!\n");

		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "room3GhostDead");
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "candlesMelted");
		GameState_ChangeGhostPos(gameState, -3);
	}
}


/* Build a "brick" object */
Item* Sword_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("sword", "While it may be old, the sword shines like it were made of the moon itself.", true, Sword_Use, Sword_Take, NULL);
}