#pragma once

#include "CardDeck.h"
#include "ValidInput.h"

#include <stdlib.h>     
#include <time.h>       


/*
* CardShuffle Class will shuffle any number of cards in an effective and quick manner similar to shuffling a deck
* of cards in real life. Call the constructor with a parameter for the number of cards or no parameter and receive
*back a shuffled deck of cards. Has an error flag in case of an error;
*/

namespace DECKSHUFFLE
{
	class DeckShuffle
	{
	private:
		std::vector< std::vector <unsigned int> > * cardDeck;
		unsigned int deckShuffleError;
		unsigned int cardSize;

	public:
		explicit DeckShuffle(CARDDECK::CardDeck & deck);
		DeckShuffle();
		unsigned int returnError() { return deckShuffleError; }				//Inline function, Getter
		void shuffleDeck();
		void splitDeck(unsigned int splitsParam = 1);
		void zipperShuffle();
	};
}
//#endif // !DeckShuffle_H