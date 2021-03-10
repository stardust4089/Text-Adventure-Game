
#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "MirrorFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "EggFunctions.h" /* Egg_Build */


/* Helper: The action performed when the brick is taken. */
void Mirror_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the brick might be used, whenever it is picked up. */
	printf("The mirror glimmers in the torchlight. Items veiwed throguh it are stranglely not reversed, and also have some kind of blue haze.\n");
}


/* Helper: The action performed when the brick is used. */
void Mirror_Use(CommandContext context, GameState* gameState, WorldData* worldData)
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
		printf("You must have the mirror before you can use it.\n");
		return;
	}

	/* check if we're in the right room to use the item */
	if (gameState->currentRoomIndex != 6 || !GameFlags_IsInList(gameState->gameFlags, "DeskDrawerOpened"))
	{
		/* we are not in the right room - inform the user of the problem and take no action */
		printf("The mirror has no new effect on these objects.\n");
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

		printf("As you pull out the mirror, you see the paper glimmer in its pristine veiw. Slowly, text begins to form on the paper. It reads: Always remember MADELINE");
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "PasswordDiscovered");
	}
}


/* Build a "brick" object */
Item* Mirror_Build()
{
	/* Create a "brick" item, using the functions defined in this file */
	return Item_Create("handheld mirror", "A handheld mirror that doesnt flip the images", true, Mirror_Use, Mirror_Take, NULL);
}