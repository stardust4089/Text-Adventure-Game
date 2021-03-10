/******************************************************************************
filename    GoldPieceFunctions.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "gold piece".

******************************************************************************/
#include "stdafx.h"
#include "GoldPieceFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "DeskKeyFunctions.h"
#include "WorldData.h"
#include "ItemList.h"
#include "DeskKeyFunctions.h"
typedef struct WorldData WorldData;


/* Helper: The action performed when the gold piece is taken. */
void GoldPiece_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the gold piece has already been scored */
	if (!GameFlags_IsInList(gameState->gameFlags, "goldPieceScored"))
	{
		/* tell the user that something cool happens when they pick up the gold piece */
		printf("The gold piece burns in your hand.  You're rich!\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 5);
		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "goldPieceScored");
	}
}

void GoldPiece_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* gold; /* The brick in the player's inventory */
	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the brick out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("You must have the gold before you can use it.\n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 7)
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("There is no apparent use for the gold piece here.\n");
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
		gold = ItemList_FindItem(gameState->inventory, "gold piece");

		/* Remove the brick from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, gold);

		/* Tell the user what they did */
		printf("You present the gold pice to Gadrax. Seeing the shimmering gold, his fearful expression slowly turns into a smirk.\n\"Well, I see someone knows how to barter. Good luck escaping! Here's your key.\"\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 10);

		gameState->inventory = ItemList_Add(gameState->inventory, SmallKey_Build());

	}
}


/* Build a "gold piece" object */
Item* GoldPiece_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("gold piece", "A small piece of gold\n", true, GoldPiece_Use, GoldPiece_Take, NULL);
}