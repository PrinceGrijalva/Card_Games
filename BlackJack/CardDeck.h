#ifndef CardDeck_H
#define CardDeck_H

#include <iostream>
#include <vector>

/*
* CardDeck class is meant to define what the <values> of each card is held within a card vector, how large the size 
* of the deck of cards is, print out the deck in order from 0 - deckSize-1. 
* 1. Playing card deck : Hold the deck as a vector of vectors of unsigned ints. The outer vector
* holds the individual "cards" and the inner vector holds unsigned ints which represent the 3 values 
* of a deck of normal playing cards: deck number, suit, value respectably.
*
* 2. Other kind of card deck can be represented by the vector of vectors of unsigned ints
*/

//Constant size of a standard deck of playing cards. (INTERNAL LINKAGE)
namespace
{
	const int STD_DECK_SIZE = 52;
}

namespace CARDDECK
{
	class CardDeck
	{
	private:	
		unsigned int numOfDecks;
		unsigned int totalCards;
		std::vector< std::vector <unsigned int> > vectorDeck;

		void createPlayingCards();

	public:
		explicit CardDeck(unsigned int decks);
		CardDeck();
		unsigned int getTotalCards() const { return totalCards; }							// Inline function
		std::vector< std::vector <unsigned int> >* getVectorDeck() { return &vectorDeck; }	// Inline function
		void printDeck() const;
	};
}

#endif // !CardDeck_H