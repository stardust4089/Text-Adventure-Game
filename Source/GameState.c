/******************************************************************************
filename    GameState.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file implements the GameState interface, which is used to reflect the user state
in the game.

******************************************************************************/
/* from GameState.h: stdafx.h, used here for NULL, malloc/free, printf */
#include "GameState.h" /* Function declarations */
#include "ItemList.h" /* ItemList_Free */
#include "GameFlags.h" /* GameFlags_Free */

/* Create an empty game state object */
GameState* GameState_Create()
{
	GameState* gameState; /* the new object we will return */

	/* allocate memory for the new object */
	gameState = (GameState*)malloc(sizeof(GameState));
	if (gameState == NULL)
	{
		return NULL; /* malloc can fail! */
	}

	/* assign empty values to all members */
	gameState->score = 0;
	gameState->ghostLevel = 0;
	gameState->currentRoomIndex = 0;
	gameState->inventory = NULL;
	gameState->gameFlags = NULL;
	gameState->isRunning = true;

	/* return the new object */
	return gameState;
}


/* Free the memory associated with a game-state object */
void GameState_Free(GameState** gameStatePtr)
{
	/* safety check on the parameters */
	if ((gameStatePtr == NULL) || (*gameStatePtr == NULL))
	{
		return; /* take no action if no valid object was provided */
	}

	/* free the inventory */
	ItemList_Free(&(*gameStatePtr)->inventory);

	/* free the game flags */
	GameFlags_Free(&(*gameStatePtr)->gameFlags);

	/* free the object */
	free(*gameStatePtr);

	/* set the incoming pointer to NULL*/
	*gameStatePtr = NULL;
}


/* Modify the score, with appropriate user information */
void GameState_ChangeScore(GameState* gameState, int modifier)
{
	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if any action is needed*/
	if (modifier == 0)
	{
		return; /* no action needed */
	}

	/* modify the score */
	gameState->score += modifier;

	/* check if the modifier is positive or negative */
	if (modifier > 0)
	{
		/* the modifier was positive, so output a positive message */
		printf("You have gained %d points.  ", modifier);
	}
	else
	{
		/* the modifier was negative, so output a negative message */
		printf("You have lost %d points.  ", modifier);
	}

	/* output the new score total */
	printf("Your new score is %d.\n", gameState->score);
}


/* Modify the score, with appropriate user information */
void GameState_ChangeGhostPos(GameState* gameState, int modifier)
{
	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if any action is needed*/
	if (modifier == 0)
	{
		return; /* no action needed */
	}
	/* modify the score */
	gameState->ghostLevel += modifier;
	
	if (gameState->currentRoomIndex != 3)
	{
	
		if (gameState->ghostLevel == 1)
			printf("There is a slight wooshing sound as your mind fumbles, almost like something is creeping up on you.\n");
		if (gameState->ghostLevel == 2)
			printf("The sound of rattling chains continues to get louder. It seems the ghosts are drawing nearer!\n");
		if (gameState->ghostLevel >= 3)
		{
			printf("Due to your fumbling, the ghosts have finally caught up to you. You mind fills with their screams, and then everything goes black.\n");
			GameState_EndGame(gameState, "							YOU LOSE\n\n\n");
		}
		
	}
	else
	{
		if (gameState->ghostLevel < 0)
			gameState->ghostLevel = 0;
		if (gameState->ghostLevel == 1)
			printf("The ghost draws ever closer!\n");
		if (gameState->ghostLevel == 2)
			printf("Your mind is dominated by fear as the ghost stares into your being, drawing closer and closer!\n");
		if (gameState->ghostLevel >= 3)
		{
			printf("Due to your fumbling, the ghost caught up to you. You mind fills with it's screeches, and then everything goes black.\n");
			GameState_EndGame(gameState, "							YOU LOSE\n\n\n");
			return;
		}
	}
	

}

/* End the game, with appropriate user information */
void GameState_EndGame(GameState* gameState, const char* message)
{
	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* if a message was provided, output it now */
	if (message != NULL)
	{
		printf(message);
	}

	/* output the final score */
	printf("Your final score is %d.\n\n", gameState->score);

	/* output a clean goodbye message, so the user knows the game is exiting intentionally */
	printf("Goodbye!\n\n");

	/* set the isRunning state so the game quits on the next loop */
	gameState->isRunning = false;
}