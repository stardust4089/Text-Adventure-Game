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
#include "NPC.h"
#include "Desk.h"
#include "Chest.h"
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

	room = Room_Create("As you enter, a ghost flies out the wall and begins charging you, unleashing an otherworldly scream. Beside your feet, you see the hollow corpse of a knight.\n");

	Room_AddRoomExit(room, "south", 1);
	Room_AddRoomExitShortcut(room, "s", 1);
	ItemList_AddItem(Room_GetItemList(room), KnightCorpse_Build());
	ItemList_AddItem(Room_GetItemList(room), Sword_Build());
	/* return the new room */
	return room;
}
/* TODO ADVANCED: Build room 4 */
Room* Room4_Build()
{
	Room* room = NULL;

	room = Room_Create("Within this room, you see a tall dark oak door that in another time may have been farily ornate, though is rotten now. You also see a large chest in the corner of the room.\n");

	Room_AddRoomExit(room, "south", 2);
	Room_AddRoomExitShortcut(room, "s", 2);
	ItemList_AddItem(Room_GetItemList(room), Chest_Build());
	Room_AddRoomExit(room, "north", 6);
	Room_AddRoomExitShortcut(room, "through oaken door", 6);
	/* return the new room */
	return room;
}

Room* Room5_Build()
{
	Room* room = NULL;

	room = Room_Create("You head up a set of stairs that leads onto a sort of staging area. Within lies a large door with no visible lock, doorknob, or keyhole.\n");

	Room_AddRoomExit(room, "south", 2);
	Room_AddRoomExitShortcut(room, "s", 2);
	//ADD EXIT DOOR ONE THAT NEEDS PLAYER TO SPEAK THE PASSWORD OUT LOUD.
	Room_AddRoomExit(room, "east", 7);
	Room_AddRoomExitShortcut(room, "e", 7);
	Room_AddRoomExit(room, "west", 6);
	Room_AddRoomExitShortcut(room, "w", 6);
	/* return the new room */
	
	return room;
}

Room* Room6_Build()
{
	Room* room = NULL;

	room = Room_Create("Making your way through the holes in the old rotten door, you find yourslef in a small library. Around you are bookshelves with old deteritating leatherbound titles, and a anceint desk sitting in the center.\n");

	Room_AddRoomExit(room, "south", 4);
	Room_AddRoomExitShortcut(room, "s", 4);
	ItemList_AddItem(Room_GetItemList(room), Desk_Build());
	Room_AddRoomExit(room, "east", 5);
	Room_AddRoomExitShortcut(room, "e", 5);
	/* return the new room */
	return room;
}
Room* Room7_Build()
{
	Room* room = NULL;

	room = Room_Create("You appear to enter some sort of laboratory. Around you are beakers, wires, strange metal rods, and other alchemical supplies. In the corner is a very hold man with his head in his hands in curled up and shuddering.\n");

	Room_AddRoomExit(room, "west", 5);
	//ADD NPC
	ItemList_AddItem(Room_GetItemList(room), NPC_Build());

	/* return the new room */
	return room;
}
Room* Room8_Build()
{
	Room* room = NULL;

	room = Room_Create("You pass through the golden door to find yourself facing another door that looks as thoguh it belongs to a large vault door. In the center is a large golden keyhole.\n");

	Room_AddRoomExit(room, "south", 3);
	//ADD GOLDEN KEY DOOR. ONCE PLAYER OPENS IT THEY WIN.


	/* return the new room */
	return room;
}


/* ------------------------------------------------------- */
/* Create the world data for a new game */
/* ------------------------------------------------------- */
WorldData* CreateInitialWorldData()
{
	/* The new world data */
	WorldData* worldData;

	/* TODO REQUIRED: update room count to match the number of rooms you have created and added to the world
	   if this number doesn't match then your game will either crash or you will end up stuck in a broken room with no exits */
	int roomCount = 9;

	/* create the new WorldData object with 3 rooms */
	worldData = WorldData_Create("Welcome to my GAM100 Game!\n\n", roomCount);

	/* build each room and assign them to the world data */
	
	WorldData_SetRoom(worldData, 0, Room0_Build());
	WorldData_SetRoom(worldData, 1, Room1_Build());
	WorldData_SetRoom(worldData, 2, Room2_Build());
	WorldData_SetRoom(worldData, 3, Room3_Build());
	WorldData_SetRoom(worldData, 4, Room4_Build());
	WorldData_SetRoom(worldData, 5, Room5_Build());
	WorldData_SetRoom(worldData, 6, Room6_Build());
	WorldData_SetRoom(worldData, 7, Room7_Build());
	WorldData_SetRoom(worldData, 8, Room8_Build());
	
	/* return the new object */
	return worldData;
}