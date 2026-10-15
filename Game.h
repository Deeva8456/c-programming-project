/**
 * @file game.h
 * @brief Public interface for the card game logic.
 *
 * This module implements all gameplay mechanics:
 *  - shuffling
 *  - sorting
 *  - dealing
 *  - turn-taking
 *  - reshuffling played pile back to hidden deck
 *  - determining a winner
 * * @author Deeva Mohamed
 * @date 27/11/2025
 */

#ifndef GAME_H
#define GAME_H

#include "carddeck.h"
#include "card.h"



 /**
  * @brief Run the full card game.
  * @param packs Number of packs used to create the game deck.
  *
  * This function executes:
  *  - deck creation
  *  - shuffling
  *  - dealing to both players
  *  - turn loop until a player wins
  */
void playGame(int packs);

#endif

