#pragma once
#ifndef CardDeck_H
#define CardDeck_H

/**
* CardDeck class is meant to define what the <value> of each card is, how large the size of the deck of cards is,
* print out the deck in order from 0 - deckSize, and hold the deck as an array of <value>s in which arrDeck 
* points to the first card.
*/

class CardDeck
{
	//Allow DeckShuffle access to private variables
	friend class DeckShuffle;

public:
	//Construct CardDeck with parameter passed or default value of 52; explicit needed because constructor has 
	//only one parameter.
	explicit CardDeck( unsigned int whichGame = 0);

	//Destructor to free memory.
	~CardDeck();

	//Copy constructor for pointers.
	CardDeck(const CardDeck & rhs);

	//Overloard operator= for working with pointers.
	const CardDeck & operator=(const CardDeck & rhs);

	//Copies changes made to the deck
	void copyDeck(int * deckToCopy);

	//Prints out deck based on first - last/ 0 - deckSize-1.
	void printDeck();

	//Returns CardDeck to be manipulated by another function, i.e. DeckShuffle()
	//int* ReturnDeck();

private:
	unsigned int game;
	unsigned int deckSize;
	int * arrDeck;
	struct cardGame 
	{
		unsigned int deck;
		unsigned int cardIndexNum;
		unsigned int suit;
		unsigned int cardNumber;
	};
};

#endif // !CardDeck_H