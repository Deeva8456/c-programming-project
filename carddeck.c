/**
 * @file carddeck.c
 * @brief Implementation of CardDeck ADT (linked list) matching carddeck.h
 *
 * This file implements the CardDeck functions declared in carddeck.h:
 *  - initCardDeck
 *  - createCardDeck
 *  - freeCardDeck
 *  - addCardTop
 *  - addCardBottom
 *  - removeTopCard
 *  - removeCardAt
 *  - deckSize
 *  - isDeckEmpty
 *  - deckToArray
 *@author DEEVA.MOHAMED 
 * @date 26/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "carddeck.h"

 // Internal helper: allocate a new node                                      
 /**
  * @brief Allocate and initialize a CardNode for card c.
  * @param c Card to store in the new node.
  * @return CardNode* Pointer to newly allocated node (never NULL; exits on error).
  */
static CardNode* createNode(Card c)
{
    CardNode* node = (CardNode*)malloc(sizeof(CardNode));
    if (node == NULL) {
        //  fprintf to stderr - correct usage 
        fprintf(stderr, "Error: malloc failed in createNode()\n");
        exit(EXIT_FAILURE);
    }

    node->card = c;
    node->next = NULL;
    return node;
}

// initCardDeck                                                              
/**
 * @brief Initialize an empty CardDeck.
 * @param deck Pointer to the CardDeck to initialize.
 *
 * Sets head to NULL and size to zero. This function is called before
 * using the deck.
 */
void initCardDeck(CardDeck* deck)
{
    if (deck == NULL)
        return;
    deck->head = NULL;
    deck->size = 0;
}

// addCardTop                                                                
/**
 * @brief Add a card to the top of the deck (head insertion).
 * @param deck Pointer to the CardDeck.
 * @param c Card to add.
 */
void addCardTop(CardDeck* deck, Card c)
{
    if (deck == NULL)
        return;

    CardNode* node = createNode(c);
    // Insert at head 
    node->next = deck->head;
    deck->head = node;
    deck->size++;
}


// addCardBottom                                                             

/**
 * @brief Add a card to the bottom of the deck.
 * @param deck Pointer to the CardDeck.
 * @param c Card to add.
 *
 * Traverses to the end of the list and appends the new node. If the deck is
 * empty the node becomes the head.
 */
void addCardBottom(CardDeck* deck, Card c)
{
    if (deck == NULL)
        return;

    CardNode* node = createNode(c);

    if (deck->head == NULL) {
        //Empty deck: new node becomes head 
        deck->head = node;
    }
    else {
        // Traverse to last node 
        CardNode* cur = deck->head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = node;
    }
    deck->size++;
}

// removeTopCard                                                             
/**
 * @brief Remove the top card from the deck.
 * @param deck Pointer to the CardDeck.
 * @param out Pointer to Card where removed card will be stored (may be NULL).
 * @return int 1 on success (card removed), 0 if deck was empty or deck == NULL.
 *
 * Removes the head node, copies its Card into *out (if out != NULL), frees the
 * node and decrements deck size.
 */
int removeTopCard(CardDeck* deck, Card* out)
{
    if (deck == NULL || deck->head == NULL)
        return 0; // nothing to remove 

    CardNode* node = deck->head;
    deck->head = node->next; // advance head 

    if (out != NULL)
        *out = node->card; // copy card out 

    free(node);
    deck->size--;
    return 1;
}

// removeCardAt                                                               
/**
 * @brief Remove the card at a specified 0-based index.
 * @param deck Pointer to the CardDeck.
 * @param index 0-based index (0 = top).
 * @param out Pointer to Card to receive removed card (may be NULL).
 * @return int 1 on success, 0 on failure (invalid index or empty deck).
 *
 * This function is useful for shuffle implementations which remove the
 * r-th card.
 */
int removeCardAt(CardDeck* deck, int index, Card* out)
{
    if (deck == NULL || deck->head == NULL)
        return 0;

    if (index < 0 || index >= deck->size)
        return 0; // invalid index 

    if (index == 0)
        return removeTopCard(deck, out); // delegate 

    // Find node before target 
    CardNode* prev = deck->head;
    for (int i = 0; i < index - 1; i++) {
        //prev should never be NULL here because index is valid 
        prev = prev->next;
    }

    CardNode* target = prev->next;
    prev->next = target->next; //unlink target 

    if (out != NULL)
        *out = target->card; //copy card out 

    free(target);
    deck->size--;
    return 1;
}

// deckSize                                                                   
/**
 * @brief Return the number of cards in the deck.
 * @param deck Pointer to the CardDeck.
 * @return int Number of cards (0 if deck == NULL).
 */
int deckSize(const CardDeck* deck)
{
    if (deck == NULL)
        return 0;
    return deck->size;
}

//isDeckEmpty                                                                
/**
 * @brief Return 1 if deck is empty, 0 otherwise.
 * @param deck Pointer to the CardDeck.
 * @return int 1 if empty or deck == NULL, 0 otherwise.
 */
int isDeckEmpty(const CardDeck* deck)
{
    if (deck == NULL)
        return 1;
    return (deck->size == 0);
}

// deckToArray                                                                
/**
 * @brief Convert the deck into a dynamically-allocated array of Card.
 * @param deck Pointer to the CardDeck.
 * @return Card* Pointer to newly-allocated array (caller must free), or NULL
 *         if deck is empty or deck == NULL. The order is top (index 0) to
 *         bottom (index size-1).
 */
Card* deckToArray(const CardDeck* deck)
{
    if (deck == NULL || deck->size == 0)
        return NULL;

    Card* arr = (Card*)malloc(sizeof(Card) * deck->size);
    if (arr == NULL) {
        fprintf(stderr, "Error: malloc failed in deckToArray()\n");
        exit(EXIT_FAILURE);
    }

    CardNode* cur = deck->head;
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur->card; //copy card 
        cur = cur->next;
    }
    return arr;
}

// createCardDeck                                                             
/**
 * @brief Create a deck containing `packs * 52` cards in standard order.
 * @param deck Pointer to the CardDeck to populate.
 * @param packs Number of 52-card packs (>= 0). If packs <= 0 the deck is left empty.
 *
 * The order chosen is: for each pack, suit CLUB..DIAMOND; for each suit,
 * rank TWO..ACE. Cards are appended to the bottom so the first card inserted
 * will be at the top if removed with successive removeTopCard calls depending
 * on whether you push to top/bottom in your dealing logic.
 */
void createCardDeck(CardDeck* deck, int packs)
{
    if (deck == NULL)
        return;

    initCardDeck(deck);

    if (packs <= 0)
        return;

    for (int p = 0; p < packs; p++) {
        for (int s = CLUB; s <= DIAMOND; s++) {
            for (int r = TWO; r <= ACE; r++) {
                Card c;
                c.suit = (Suit)s;
                c.rank = (Rank)r;
                // Append to bottom to keep natural order per pack 
                addCardBottom(deck, c);
            }
        }
    }
}

// freeCardDeck                                                               
/**
 * @brief Free all memory used by the deck and reset it.
 * @param deck Pointer to the CardDeck to free.
 */
void freeCardDeck(CardDeck* deck)
{
    if (deck == NULL)
        return;

    CardNode* cur = deck->head;
    while (cur != NULL) {
        CardNode* next = cur->next;
        free(cur);
        cur = next;
    }
    deck->head = NULL;
    deck->size = 0;
}
