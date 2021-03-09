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
#include "EggFunctions.h" /* Egg_Build */


/* Helper: The action performed when the brick is taken. */
void GoldKey_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the brick might be used, whenever it is picked up. */
	printf("The key is old and rusted. It feels strangly dense for its size.\n");
}


/* Helper: The action performed when the brick is used. */
void GoldKey_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* brick; /* The brick in the player's inventory */
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
	if (gameState->currentRoomIndex != 0)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the key here.\n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "cageBrokenScored"))
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

		/* Find the brick in the player's inventory - it should be there, since we are in the Inventory context */
		brick = ItemList_FindItem(gameState->inventory, "brick");

		/* Remove the brick from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, brick);

		/* Tell the user what they did */
		printf("You insert the key into the lock. With a creaking and shuddering, the ancient lock clicks open and the door swings open.\nYou may now use the north door.\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 0.  There is an unlocked prision door here.\n");

		/* Add the exit door to the room, as now the cage in unlocked.*/
		Room_AddRoomExit(room, "north", 1);
		/* TODO BASIC: Add room exit shortcut for "n" */
		Room_AddRoomExitShortcut(room, "n", 1);
		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "cageBrokenScored");
	}
}


/* Build a "brick" object */
Item* GoldKey_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("gold key", "A small rusted and corroded key.", true, GoldKey_Use, GoldKey_Take, NULL);
}