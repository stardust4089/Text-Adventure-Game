/******************************************************************************
filename    LookCommandHandler.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "look" user command, which outputs
a description of an item or the current room.

******************************************************************************/
#include "stdafx.h" /* NULL, printf, strnlen_s */
#include "LookCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_Print, Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem */
#include "Item.h" /* Item_Print */


/* Handles the "talk" command, which outputs a description of an item or the current room */
void HandleTalkCommand(CommandData* command, GameState* gameState, WorldData* worldData)
{
	if (gameState->currentRoomIndex != 7)
	{
		printf("There is no one to talk to here.");
		return;
	}
	else
	{
		Room* room; /* the current room */
		/*
		Item* item; /* the item referred to by the command noun, if any */

		ItemList** roomItemsPtr; /* the list of items in the room */
		/* safety check on the parameters */
		if ((command == NULL) || (gameState == NULL) || (worldData == NULL)) 
		{
			return; /* take no action if the parameters are invalid */
		}

		
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
	
		roomItemsPtr = Room_GetItemList(room);
		/*
		item = ItemList_FindItem(*roomItemsPtr, Item_GetName(item));
		*/
		if (roomItemsPtr == NULL)
		{
			return; /* the item list pointer is missing - something has gone wrong.  take no action */
		}
	
		if ((command->noun == NULL) || (strnlen_s(command->noun, MAX_COMMAND_NOUN_LENGTH) == 0))
		{
			printf("The man introduces himself.\n My...my name is Gadrax. It's jsut me here now. Just me, and my friends...\n\nTalk options: \n -Friends? \n -Where? \n -Prision? \n Ghosts?\n");
			return;
		}
		else if (strcmp(command->noun, "friends") == 0)
		{
			printf("My friends! My beutiful creations. After all this time, I've brought them back. Finally, I can be with my family again.\n\nTalk options: \n -Family? \n -Where? \n -Prision? \n");
			return;
		}
		else if (strcmp(command->noun, "where") == 0)
		{
			printf("Where are we? Oh, we are in my amazing, marvelous labratory. Nobody thoguht it could be done, they locked me away in here. But they didnt know how far my alchemical skill had come since the accident.\n\nTalk options: \n -Accident? \n -Friends? \n -Prision? \n");
			return;
		}
		else if (strcmp(command->noun, "prision") == 0)
		{
			printf("Oh, poor, poor gadrax. His attempt to escape did not scuceed! Instead you are trapped in here as well, like all the others... My friends won't let me leave! If only the voices would leave me alone!\n\nTalk options: \n -Voices? \n -Friends? \n -Where? \n");
			return;
		}
		else if (strcmp(command->noun, "voices") == 0)
		{
			printf("They talk to me, you know. My family, my friends! I am the greatest alchemist alive, for I can speak to them, talk to them.... be with them again. \n\nTalk options: \n -Ghosts? \n -Friends? \n -Escape? \n");
			return;
		}
		else if (strcmp(command->noun, "accident") == 0)
		{
			printf("Oh, what a terrible day that was! I had just prefected it, PERFECTED i saw, my way of turning lead to gold... but then, something went terribly wrong! my lab was destryoed and my family along with it. So i was banished from the kingdom, forced to live imprisioned here as bait for the odd adventurer who wishes to slay my friends. At least to voices keep me company.\n\nTalk options: \n -Voices? \n -Escape? \n -Friends? \n");
			return;
		}
		else if (strcmp(command->noun, "family") == 0)
		{
			printf("They were amazing...werent they? Everything you could ask for....But after the accident, i could no longer live with myself...live by myself. So I made it my work to bring them back, no matter the price. Oh, what a price it truely was...\n\nTalk options: \n -Accident? \n -Escape? \n -Where? \n");
			return;
		}
		else if (strcmp(command->noun, "ghosts") == 0)
		{
			printf("Sometimes the voices go quitet... and I see things I dont want to see.Swirling wraithsand ghosts of darkness, evil spirits conjured from...my summoning ? Some would call me a necromancer, some would come here to just hunt me down.It almost seems that the dead...dont want me anymore...\n\nTalk options: \n -Escape? \n -Friends? \n -Where? \n");
			return;
		}
		else if (strcmp(command->noun, "escape") == 0)
		{
			printf("You... you want to escape? You want to leave me here... all alone? Well, I suppose that is to be expected... Though I do not remeber how, the voices wont let me remember. I do have this key here, but i don't know what it was for....\n\nTalk options: \n -Key? \n -Friends? \n -Where? \n");
			return;
		}
		else if (strcmp(command->noun, "key") == 0)
		{
			printf("You! I knew you were a theif, another hero, another one who'd come and try to take what is rightfully MINE! Unless, of course... you offer something in return?\n\nTalk options: \n -Key? \n -Friends? \n -Where? \n");
			return;
		}
		else
		{			
			/* the noun didn't match an available person or option, so inform the user that there is no match */
			printf("The man does not understand your question.\n");
			return;
		}
	}
	
	
}