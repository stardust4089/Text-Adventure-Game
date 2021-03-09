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
#include "SilverKeyFunctions.h"
#include "BronzeKeyFunctions.h"
#include "GoldKeyFunctions.h"


void Candleabra_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	UNREFERENCED_PARAMETER(context);

	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room 
	Item* silverKey;
	Item* bronzeKey;
	Item* goldKey;
	*/
	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	
	if (!(GameFlags_IsInList(gameState->gameFlags, "candlesMelted")))
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("You must wait for the candles to melt before you can grab the items!\n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 2)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("You cannot use the candleabra here.\n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "candleKeysRemoved") && GameFlags_IsInList(gameState->gameFlags, "candlesMelted"))
	{
		/* the player already used the brick - inform the user of the problem and take no action */
		printf("The candles are melted and the keys have been taken, there is no more use for the candleabra.\n");
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

		gameState->inventory = ItemList_Add(gameState->inventory, SilverKey_Build());
		gameState->inventory = ItemList_Add(gameState->inventory, BronzeKey_Build());
		gameState->inventory = ItemList_Add(gameState->inventory, GoldKey_Build());

		printf("You take the keys out of the cold melted stumps of the candles. Check your inventory!\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 2.  There is a candleabra with 3 melted candles in it that once held keys.\n");

		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "candleKeysRemoved");
	}
}

/* Build a "brick" object */
Item* Candleabra_Build()
{	
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("candleabra", "On further inspection, you see the handle of a gold, bronze, and silver key buried within each candle.", false, Candleabra_Use, NULL, NULL);
}
