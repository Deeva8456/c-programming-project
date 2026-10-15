/**
 * @file game.c
 * @brief Implementation of gameplay mechanics for the two-player card game.
 *
 * This file contains the full game logic used by main.c, including:
 *  - Deck shuffling 
 *  - Deck sorting 
 *  - Dealing cards to players
 *  - Handling the discard and hidden piles
 *  - Automatically reshuffling when the hidden deck becomes empty
 *  - The complete turn-based game loop
 *
 * The game works with the dynamic CardDeck type (singly-linked list).
 * Each player draws or plays depending on whether they have a matching card.
 *
 * @author DARRAGH.O'SULLIVAN & ABEL ABRAHAM.VALIYAKALAYIL
 * @date 27/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "card.h"
#include "carddeck.h"

 //External card functions from card.c 
extern const char* card_to_string(Card c);
extern void card_print(Card c, int newline);
extern int card_matches(Card a, Card b);


 //UTILITY PRINT FUNCTION

 /**
  * @brief Print all cards in a deck on one line.
  * @param deck Pointer to a CardDeck.
  */
static void printDeckSimple(const CardDeck* deck)
{
    CardNode* cur = deck->head;
    while (cur) {
        card_print(cur->card, 0);
        printf(" ");
        cur = cur->next;
    }
    printf("\n");
}



  //SHUFFLE + SORT IMPLEMENTATIONS

 /**
  * @brief Comparator for qsort used when sorting cards.
  */
static int card_cmp_qsort(const void* pa, const void* pb)
{
    const Card* a = pa;
    const Card* b = pb;

    if (a->suit != b->suit)
        return a->suit - b->suit;

    return a->rank - b->rank;
}

/**
 * @brief Shuffle a deck using Fisher-Yates algorithm.
 * @param deck Pointer to the deck to shuffle.
 */
static void shuffle_deck(CardDeck* deck)
{
    int n = deckSize(deck);
    if (n <= 1) return;

    // Convert linked list to array 
    Card* arr = deckToArray(deck);
    if (!arr) return;

    //  shuffle 
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    // Rebuild deck from array 
    freeCardDeck(deck);
    for (int i = 0; i < n; i++)
        addCardBottom(deck, arr[i]);

    free(arr);
}

/**
 * @brief Sort a deck using qsort.
 * @param deck Pointer to the deck to sort.
 */
static void sort_deck(CardDeck* deck)
{
    int n = deckSize(deck);
    if (n <= 1) return;

    Card* arr = deckToArray(deck);
    if (!arr) return;

    qsort(arr, n, sizeof(Card), card_cmp_qsort);

    freeCardDeck(deck);
    for (int i = 0; i < n; i++)
        addCardBottom(deck, arr[i]);

    free(arr);
}



  //GAMEPLAY SUPPORT FUNCTIONS

 /**
  * @brief Find the index of a playable card in a player's deck.
  * @param deck Player hand.
  * @param top Card currently on discard pile.
  * @return index of playable card, or -1 if none.
  */
static int findPlayableIndex(const CardDeck* deck, Card top)
{
    CardNode* cur = deck->head;
    int idx = 0;

    while (cur) {
        if (card_matches(cur->card, top))
            return idx;
        idx++;
        cur = cur->next;
    }
    return -1;
}

/**
 * @brief Give each player 8 starting cards from the hidden deck.
 */
static void deal_initial_hands(CardDeck* hidden, CardDeck* p1, CardDeck* p2)
{
    for (int i = 0; i < 8; i++) {
        Card c;
        if (removeTopCard(hidden, &c)) addCardTop(p1, c);
        if (removeTopCard(hidden, &c)) addCardTop(p2, c);
    }
}

/**
 * @brief Refill the hidden deck by reshuffling the played pile.
 *
 * Leaves the top discard card in place.
 */
static void reshuffle_played_into_hidden(CardDeck* hidden, CardDeck* played)
{
    // Hidden deck must be empty before reshuffling 
    if (!isDeckEmpty(hidden)) return;

    // Need at least 2 cards in played pile 
    if (deckSize(played) <= 1) return;

    // Save top card (must stay on table) 
    Card top;
    removeTopCard(played, &top);

    CardDeck temp;
    initCardDeck(&temp);

    //Move remaining played cards into temp 
    Card c;
    while (removeTopCard(played, &c))
        addCardBottom(&temp, c);

    // Shuffle temp and refill hidden deck 
    shuffle_deck(&temp);

    while (removeTopCard(&temp, &c))
        addCardBottom(hidden, c);

    //Restore top card to played pile 
    addCardTop(played, top);

    freeCardDeck(&temp);
}



 //  MAIN GAME LOOP

 /**
  * @brief Start and run the full two-player card game.
  *
  * This function:
  *  - Creates and shuffles a hidden deck
  *  - Deals 8 cards per player
  *  - Sorts both hands
  *  - Begins the turn-based game loop
  *  - Handles drawing, playing, reshuffling, and winning
  *
  * @param packs Number of packs used to build the deck.
  */
void playGame(int packs)
{
    srand((unsigned)time(NULL));

    CardDeck hidden, played, p1, p2;
    initCardDeck(&hidden);
    initCardDeck(&played);
    initCardDeck(&p1);
    initCardDeck(&p2);

    // Create + shuffle hidden deck 
    createCardDeck(&hidden, packs);
    shuffle_deck(&hidden);

    // Deal cards 
    deal_initial_hands(&hidden, &p1, &p2);

    //Sort hands 
    sort_deck(&p1);
    sort_deck(&p2);

    printf("\nPlayer 1 initial hand:\n");
    printDeckSimple(&p1);

    printf("\nPlayer 2 initial hand:\n");
    printDeckSimple(&p2);

    //Flip opening card 
    Card first;
    removeTopCard(&hidden, &first);
    addCardTop(&played, first);

    printf("\nStarting card: ");
    card_print(first, 1);

    int turn = 1;

    //MAIN GAME LOOP 
    while (1) {

        // Read top card of discard pile 
        Card top;
        removeTopCard(&played, &top);
        addCardTop(&played, top);

        printf("\n--- Player %d's turn ---\n", turn);

        // PLAYER 1 
        if (turn == 1) {
            int idx = findPlayableIndex(&p1, top);

            if (idx >= 0) {
                // Play a card 
                Card c; removeCardAt(&p1, idx, &c);
                addCardTop(&played, c);
                printf("Player 1 plays: ");
                card_print(c, 1);
            }
            else {
                // Draw a card 
                printf("Player 1 draws...\n");

                if (isDeckEmpty(&hidden))
                    reshuffle_played_into_hidden(&hidden, &played);

                Card c;
                if (removeTopCard(&hidden, &c)) {
                    addCardTop(&p1, c);
                    printf("Player 1 drew: ");
                    card_print(c, 1);
                }
            }

            if (deckSize(&p1) == 0) {
                printf("\nPLAYER 1 WINS!\n");
                break;
            }
        }

        //PLAYER 2 
        else {
            int idx = findPlayableIndex(&p2, top);

            if (idx >= 0) {
                Card c; removeCardAt(&p2, idx, &c);
                addCardTop(&played, c);
                printf("Player 2 plays: ");
                card_print(c, 1);
            }
            else {
                printf("Player 2 draws...\n");

                if (isDeckEmpty(&hidden))
                    reshuffle_played_into_hidden(&hidden, &played);

                Card c;
                if (removeTopCard(&hidden, &c)) {
                    addCardTop(&p2, c);
                    printf("Player 2 drew: ");
                    card_print(c, 1);
                }
            }

            if (deckSize(&p2) == 0) {
                printf("\nPLAYER 2 WINS!\n");
                break;
            }
        }

        //Switch turns
        turn = (turn == 1 ? 2 : 1);
    }

    // Cleanup memory 
    freeCardDeck(&hidden);
    freeCardDeck(&played);
    freeCardDeck(&p1);
    freeCardDeck(&p2);
}
