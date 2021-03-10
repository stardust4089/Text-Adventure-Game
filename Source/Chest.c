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
#include "GoldPieceFunctions.h" /* Egg_Build */


/* Helper: The action performed when the brick is taken. */
void Chest_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	UNREFERENCED_PARAMETER(context);

	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}
	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 4)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("There is no chest here.\n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "ChestOpened"))
	{
		/* the player already used the brick - inform the user of the problem and take no action */
		printf("You already opened the chest here.\n");
		return;
	}
	else
	{
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

		/* get the list of items in the current room */
		roomItemsPtr = Room_GetItemList(room);
		if (roomItemsPtr == NULL)
		{
			return; /* take no action, as something is wrong - we should always have an item list */
		}

		/* Find the brick in the player's inventory - it should be there, since we are in the Inventory context */
		

		/* Tell the user what they did */
		printf("You open up the old chest to find a single gold piece lying in the corner. It appears to have already been looted long before.\nYou may now take a gold piece.\n");
		ItemList_AddItem(Room_GetItemList(room), GoldPiece_Build());

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "ChestOpened");
	}
}

/* Build a "brick" object */
Item* Chest_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("chest", "It is an old and falling apart chest, sitting aimlessly in the corner.", false, Chest_Use, NULL, NULL);
}