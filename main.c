/**
 * @file main.c
 * @brief Entry point of the card game application.
 *
 * This file handles only user input and starts the game logic.
 * All gameplay, card handling, and rules are implemented in game.c/h.
 *
 * @author SEAN.CARROLL
 * @date 26/11/2015
 */

#include <stdio.h>
#include "game.h"

 /**
  * @brief Program entry point.
  *
  * Prompts the user to enter the number of card packs, then starts the game
  * by calling playGame() from the Game module.
  *
  * @return int Returns 0 on successful program termination.
  */
int main(void)
{
    int packs;

    printf("Enter number of packs to use (must be >=1): ");
    scanf_s("%d", &packs);   // Safe version of scanf 

    // Start the game using the requested number of packs
    playGame(packs);

    return 0;
}
