#include "DeckShuffle.h"
#include "CardDeck.h"
#include <iostream>

int main()
{
	CardDeck cards;
	cards.printDeck();
	DeckShuffle prep;
	prep.splitDeck(cards);
	cards.printDeck();
	prep.zipperShuffle(cards);
	cards.printDeck();
	return 0;
}