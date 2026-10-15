/**
 * @file card.c
 * @brief Implements helper functions for Card operations.
 * Provides string conversion, printing, matching rules, and comparison
 * functions. These utilities are used throughout the card game and
 * CardDeck ADT.
 *   @author  ABEL ABRAHAM.VALIYAKALAYIL
 * @date 26/11/25

 */

#include "card.h"
#include <stdio.h>

 // Lookup tables for suit and rank names                                     */

 // Human-readable suit names indexed by Suit enum 
static const char* SUIT_NAMES[] = {
    "Club",
    "Spade",
    "Heart",
    "Diamond"
};

// Rank names; indices 0–1 are unused to align with rank integer values 
static const char* RANK_NAMES[] = {
    NULL,       // index 0 unused 
    NULL,       // index 1 unused 
    "Two",      // 2 
    "Three",    // 3 
    "Four",     // 4 
    "Five",     // 5 
    "Six",      // 6 
    "Seven",    //7 
    "Eight",    // 8 
    "Nine",     //9 
    "Ten",      //10 
    "Jack",     //11 
    "Queen",    //12 
    "King",     // 13 
    "Ace"       // 14 
};

/* card_to_string                                                            
/**
 * @brief Convert a Card into a human-readable string.
 *
 * @details Uses a static buffer (overwritten on each call).
 *
 * @param c The card to convert.
 * @return const char* String representation (e.g., "Heart-Queen").
 */
const char* card_to_string(Card c)
{
    static char buffer[32];

    const char* suit = "UnknownSuit";
    const char* rank = "UnknownRank";

    // Look up suit string if valid 
    if (c.suit >= CLUB && c.suit <= DIAMOND)
        suit = SUIT_NAMES[c.suit];

    // Look up rank string if valid 
    if (c.rank >= TWO && c.rank <= ACE)
        rank = RANK_NAMES[c.rank];

    // Format the card name 
    snprintf(buffer, sizeof(buffer), "%s-%s", suit, rank);
    return buffer;
}

/* card_print                                                                
/**
 * @brief Print a card to stdout.
 *
 * @param c The card to print.
 * @param newline If non-zero, print newline after card.
 */
void card_print(Card c, int newline)
{
    const char* text = card_to_string(c);

    if (newline)
        printf("%s\n", text);
    else
        printf("%s", text);
}

// card_matches                                                              
/**
 * @brief Determine if two cards match by suit or rank.
 *
 * @details Matching rule used in the game:
 *  - Cards match if they share suit OR rank.
 *
 * @param a First card.
 * @param b Second card (e.g., last played card).
 * @return 1 if they match, 0 otherwise.
 */
int card_matches(Card a, Card b)
{
    //Match if suit OR rank matches 
    return (a.suit == b.suit) || (a.rank == b.rank);
}

//card_compare                                                              
/**
 * @brief Compare two cards for sorting.
 *
 * @details
 * - First compare suit.
 * - If suits are equal, compare rank.
 *
 * This produces a consistent ordering for sorting a deck or player hand.
 *
 * @param a Pointer to first card.
 * @param b Pointer to second card.
 * @return Negative if a<b, positive if a>b, 0 if equal.
 */
int card_compare(const Card* a, const Card* b)
{
    if (a->suit != b->suit)
        return (int)a->suit - (int)b->suit;

    return (int)a->rank - (int)b->rank;
}
