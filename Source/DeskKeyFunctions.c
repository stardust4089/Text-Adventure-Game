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
#include "Paper.h"


/* Helper: The action performed when the brick is taken. */
void SmallKey_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the brick might be used, whenever it is picked up. */
	printf("The key is polished and shines of bronze.\n");
}


/* Helper: The action performed when the brick is used. */
void SmallKey_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the brick out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("You must have a key before you can use it.\n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 6)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the key here.\n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "DeskDrawerOpened"))
	{
		/* the player already used the brick - inform the user of the problem and take no action */
		printf("You already used the key here.\n");
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

		/* Tell the user what they did */
		printf("You insert the key into the lock. With a creaking and shuddering, the ancient lock clicks and the the drawer unlocks\nWithin the desk drawer, you see what appears to be a blank sheet of paper.\n");
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "DeskDrawerOpened");
		ItemList_AddItem(Room_GetItemList(room), Paper_Build());
		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);
		
	}
}


/* Build a "brick" object */
Item* SmallKey_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("small key", "A small rusted key that mgith just fit into the lock of a desk or another sort of small lock.", true, SmallKey_Use, SmallKey_Take, NULL);
}