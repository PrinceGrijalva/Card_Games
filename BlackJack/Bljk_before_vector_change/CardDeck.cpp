#include "CardDeck.h"
#include <iostream>

CardDeck::CardDeck(unsigned int whichGame) : game(whichGame)
{
	//This variable could be usable to user define number of decks
	unsigned int numOfDecks = 4;
	
	//Switch statment of user input to different deck sizes
	switch (game)
	{
		case 0: deckSize = 52;
				break;
		case 1: deckSize = 52 * numOfDecks;
				break;
	}

	//Initialize arrDeck with size cardNum.
	arrDeck = new int[deckSize];
	//Fill arrDeck with 0 - deckSize-1 values; array of ints based on index.
	for (unsigned int i = 0; i < deckSize; i++)
		arrDeck[i] = i;
}

CardDeck::~CardDeck()
{
	delete[] arrDeck;
}

CardDeck::CardDeck(const CardDeck & rhs) : deckSize( rhs.deckSize )
{
	game = rhs.game;
	arrDeck = new int[deckSize];

	for (unsigned int i = 0; i < deckSize; i++)
		//arrDeck[i] = i;
		//fill this arrDeck with appropriate values based on what is in rhs arrDeck.
		*(arrDeck + i) = *(rhs.arrDeck + i);											
}

const CardDeck & CardDeck::operator=(const CardDeck & rhs)
{
	if (this != &rhs)
	{
		game = rhs.game;
		deckSize = rhs.deckSize;
		//delete any previously initialized arrDeck.
		delete[] arrDeck;
		//new arrDeck
		arrDeck = new int[deckSize];
		//fill this arrDeck with appropriate values based on what is in rhs arrDeck.
		for (unsigned int i = 0; i < deckSize; i++)
			*(arrDeck + i) = *(rhs.arrDeck + i);
	}
	return *this;
}

void CardDeck::copyDeck(int * deckToCopy)
{
	for (int i = 0; i < deckSize; i++)
		arrDeck[i] = deckToCopy[i];
}


void CardDeck::printDeck()
{
	std::cout << "[ " << arrDeck[0];
	for (unsigned int i = 1; i < deckSize - 1; i++)
		std::cout << ", " << arrDeck[i];

	if (deckSize > 1)
		std::cout << ", " << arrDeck[deckSize - 1] << " ]" << std::endl << std::endl;
	else
		std::cout << " ]" << std::endl << std::endl;
}
