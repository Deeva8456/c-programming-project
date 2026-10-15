
/**
* @file card.h
* @brief Defines Suit, Rank, and Card structures for use with the CardDeck ADT.
*
* This header provides the fundamental data types representing a single
* playing card. It is used by all modules that manipulate cards.
*  @author ABEL ABRAHAM.VALIYAKALAYIL
 * @date 26/11/25
*/
#ifndef CARD_H
#define CARD_H


/**
* @enum Suit
* @brief Represents the four suits in a standard deck.
*/
typedef enum {
	CLUB = 0, //Clubs suit 
	SPADE, // Spades suit 
	HEART, //Hearts suit 
	DIAMOND //Diamonds suit 
} Suit;


/**
* @enum Rank
* @brief Represents card ranks from Two to Ace.
*/
typedef enum {
	TWO = 2, //Rank 2
	THREE,      // Rank 3
	FOUR, // Rank 4
	FIVE, // Rank 5
	SIX, // Rank 6
	SEVEN, // Rank 7
	EIGHT, // Rank 8
	NINE, // Rank 9
	TEN, // Rank 10
	JACK, // Jack
	QUEEN, // Queen
	KING, // King
	ACE // Ace
} Rank;


/**
* @struct Card
* @brief Represents a single playing card with suit and rank.
* 
*/
typedef struct {
	Suit suit; // Suit of the card
	Rank rank; // Rank of the card
} Card;


#endif 