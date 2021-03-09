/******************************************************************************
filename    WorldDataFactory.c
author      Justin Chambers
DP email    justin.chambers@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the WorldData factory, which creates the WorldData objects used
in this game.

This could be used to create default states as well as loaded state.

******************************************************************************/
#include "WorldDataFactory.h" /* Function declarations */
#include "WorldData.h" /* WorldData_Create, WorldData_SetRoom */
#include "Room.h" /* Room_Create, Room_AddRoomExit, Room_GetItemList */
#include "ItemList.h" /* ItemList_Add */
#include "RustedKeyFunctions.h" /* Brick_Build */
#include "GoldPieceFunctions.h" /* GoldPiece_Build */
#include "ExitDoorFunctions.h" /* ExitDoor_Build */
#include "MirrorFunctions.h" /*Mirror_Build*/
#include "Corpse.h" /*Corpse_Build*/
#include "GameFlags.h" /*Gamefalgs_Add*/
#include "Candleabra.h" /*Candleabra_Build*/
#include "KnightCorpse.h"
#include "Sword.h"
#include "GameState.h"
/******************************************************************************
	Build room TEMPLATE
    Use this example function to build additional rooms
******************************************************************************/
Room* RoomN_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room;

	/* Create the room
	   include an initial room description */
	room = Room_Create("DEBUG: This is a template - Include a description for the room here\n");

	/* Exits
	   add one or more exits to allow navigation between rooms */
	Room_AddRoomExit(room, "north", 1);  /* 1 = the room index this exit connects to */

	/* Items
	   add items to the room */
	ItemList_AddItem(Room_GetItemList(room), ExitDoor_Build());

	/* Return the new room */
	return room;
}


/* TODO REQUIRED: Build room 0 */
Room* Room0_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 1 description: */
	room = Room_Create(" This is room 0. You awake in a cell. Around you, you hear chains rattling and the sounds of wind gusts, even though you appear to be underground. There is a key on a stone table. You may be able to reach the key and unlock your cell.\n");

	
	/* TODO REQUIRED: add an exit door to the list of items in the room, ExitDoor_Build() */
	ItemList_AddItem(Room_GetItemList(room), RustedKey_Build());
	/* TODO ADVANCED: (not required) update the description and add a room exit to the "east" */

	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 1 */
Room* Room1_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;
	/* TODO REQUIRED: Call Room_Create with the Room 1 description: */
	room = Room_Create("This is room 1. The room is faintly lit by some torches bound to sconces in the wall. The room reeks of rotton flesh, as you immediatly notice a corpse holding a mirror, its face stuck in an expression of terror as it gazes into the glass.\n");

	/* TODO REQUIRED: Add an Exit "through the mirror" to Room 2 */
	/* TODO BASIC: Add exit shortcuts for "through mirror" and "mirror" */
	Room_AddRoomExit(room, "north left", 2);
	Room_AddRoomExit(room, "north right", 3);
	/* TODO REQUIRED: Add an Exit "south" back to Room 0 */
	Room_AddRoomExit(room, "south", 0);
	/* TODO BASIC: Add room exit shortcut for "s" */
	Room_AddRoomExitShortcut(room, "s", 0);
	/* TODO REQUIRED: Add a brick to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), Mirror_Build());
	ItemList_AddItem(Room_GetItemList(room), Corpse_Build());
	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 2 */
Room* Room2_Build()
{
	Room* room = NULL;

	room = Room_Create("This is room 2.  Within the room, there are 3 candles in a large candleabra. Just beyond lies 2 locked doors, one with a silver and one with a bronze lock.\n");

	Room_AddRoomExit(room, "south", 1);
	Room_AddRoomExitShortcut(room, "s", 1);
	
	ItemList_AddItem(Room_GetItemList(room), Candleabra_Build());
	/* return the new room */
	return room;
}


/* TODO ADVANCED: Build room 3 */
Room* Room3_Build()
{
	Room* room = NULL;

	room = Room_Create("This is room 3. As you enter, a ghost flys out the wall and begins charging you, unleashing an otherworldly scream. Beside your feet, you see the hollow corpse of a knight.\n");

	Room_AddRoomExit(room, "south", 1);
	Room_AddRoomExitShortcut(room, "s", 1);
	ItemList_AddItem(Room_GetItemList(room), KnightCorpse_Build());
	ItemList_AddItem(Room_GetItemList(room), Sword_Build());
	/* return the new room */
	return room;
}
/* TODO ADVANCED: Build room 4 */


/* ------------------------------------------------------- */
/* Create the world data for a new game */
/* ------------------------------------------------------- */
WorldData* CreateInitialWorldData()
{
	/* The new world data */
	WorldData* worldData;

	/* TODO REQUIRED: update room count to match the number of rooms you have created and added to the world
	   if this number doesn't match then your game will either crash or you will end up stuck in a broken room with no exits */
	int roomCount = 4;

	/* create the new WorldData object with 3 rooms */
	worldData = WorldData_Create("Welcome to my GAM100 Game!\n\n", roomCount);

	/* build each room and assign them to the world data */
	WorldData_SetRoom(worldData, 0, Room0_Build());
	WorldData_SetRoom(worldData, 1, Room1_Build());
	WorldData_SetRoom(worldData, 2, Room2_Build());
	WorldData_SetRoom(worldData, 3, Room3_Build());

	/* return the new object */
	return worldData;
}