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


/* Build a "brick" object */
Item* KnightCorpse_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("knight corpse", "The corpse of a knight lies at your feet, an ancient blade clutched in its hollow grip.", false, NULL, NULL, NULL);
}