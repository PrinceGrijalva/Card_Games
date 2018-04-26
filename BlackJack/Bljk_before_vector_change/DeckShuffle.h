#pragma once
#ifndef DeckShuffle_H
#define DeckShuffle_H

#include "CardDeck.h"
#include <stdlib.h>     
#include <time.h>       
#include <iostream>

/**
* CardShuffle Class will shuffle any number of cards in an effective and quick manner similar to shuffling a deck
* of cards in real life. Call the constructor with a parameter for the number of cards or no parameter and receive
*back a shuffled deck of cards.
*/

class DeckShuffle
{
public:
	//Construct Cardshuffle with CardDeck reference to avoid copying array; explicit needed because constructor 
	//has only one parameter.
	DeckShuffle();
	//Destructor
	~DeckShuffle();
	//Copy Constructor
	DeckShuffle(const DeckShuffle & rhs);
	//operator=
	const DeckShuffle & operator=(const DeckShuffle & rhs);
	//SHUFFLE technique: cut the deck based on a random number. More info in function DeckShuffle.cpp
	/* FOR THIS FUNC MIGHT BE A BETTER IDEA TO USE A DATA STRUCTURE LIKE QUEUE 
	*IF USING A LARGE DATA SET; AVG CASE LOOKS BETTER*/
	void splitDeck(CardDeck & toShuffle, unsigned int splitsParam = 1);
	//SHUFFLE technique: zipper the two halfs of the deck together.
	void zipperShuffle(CardDeck & deckToZip);



private:
	//CardDeck deckToShuffle;
	//int * arrDeckShuffled;
};
#endif // !DeckShuffle_H