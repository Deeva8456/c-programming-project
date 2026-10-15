/**
 * @file carddeck.h
 * @brief Interface for CardDeck ADT using a dynamic linked list.
 *
 * Defines the CardNode and CardDeck structures and declares all operations
 * for manipulating a deck of cards (add/remove cards, convert to array,
 * check size/empty, create full packs, free memory).
 *
 * Used by main.c and carddeck.c to implement the card game.
 *
 * @author DEEVA.MOHAMED AND SEAN.CARROLL
 * @date 2025-02-14
 */


#ifndef CARDDECK_H
#define CARDDECK_H
#include "card.h"


/**
* @struct CardNode
* @brief A node in the singly-linked list representing a deck.
*/
typedef struct CardNode {
	Card card; //Card stored in this node
	struct CardNode* next; //Pointer to next node
} CardNode;


/**
* @struct CardDeck
* @brief Dynamic deck implemented as a singly-linked list.
*/
typedef struct {
	CardNode* head; //Pointer to first card in the deck
	int size; //Number of cards in the deck
} CardDeck;


/**
* @brief Initialize an empty deck.
* @param deck Pointer to deck.
*/
void initCardDeck(CardDeck* deck);


/**
* @brief Create a deck containing the specified number of standard packs.
* @param deck Pointer to deck.
* @param packs Number of packs (52 cards each).
*/
void createCardDeck(CardDeck * deck, int packs);
/**
 * @brief Free all memory used by the deck.
 * @param deck Pointer to deck. 
 */ 

void freeCardDeck(CardDeck* deck);

/**
* @brief Add a card to the top of the deck.
* @param deck Pointer to deck.
* @param c Card to add.
*/
void addCardTop(CardDeck* deck, Card c);


/**
* @brief Add a card to the bottom of the deck.
* @param deck Pointer to deck.
* @param c Card to add.
*/
void addCardBottom(CardDeck* deck, Card c);


/**
* @brief Remove the top card from the deck.
* @param deck Pointer to deck.
* @param out Pointer where removed card will be stored.
* @return 1 if removed, 0 if deck empty.
*/
int removeTopCard(CardDeck* deck, Card* out);


/**
* @brief Remove card at specified index.
* @param deck Pointer to deck.
* @param index 0-based index.
* @param out Pointer to store removed card.
* @return 1 if removed, 0 otherwise.
*/
int removeCardAt(CardDeck* deck, int index, Card* out);


/**
* @brief Return number of cards in deck.
*/
int deckSize(const CardDeck* deck);


/**
* @brief Returns 1 if deck empty, 0 otherwise.
*/
int isDeckEmpty(const CardDeck* deck);


/**
* @brief Convert deck to array. Caller must free returned array.
* @param deck Pointer to deck.
* @return Array of Cards.
*/
Card* deckToArray(const CardDeck* deck);
#endif