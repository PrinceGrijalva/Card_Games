#include "DeckShuffle.h"

DeckShuffle::DeckShuffle()
{

}
DeckShuffle::~DeckShuffle()
{

}
DeckShuffle::DeckShuffle(const DeckShuffle & rhs)
{

}
const DeckShuffle & DeckShuffle::operator=(const DeckShuffle & rhs)
{
	return rhs;
}
//Pick a random card from the deck at any position except the last one, random = 1 - n-1;
// >Break cards into two groups, every card < random number and every card a >= random number.
// >Move 1st group to the rhs of all of the 2nd group.
void DeckShuffle::splitDeck(CardDeck & toSplit, unsigned int splitsParam)
{
	//Always initialize variables in c++
	unsigned int numOfSplits = 0;
	unsigned int randPivotCard = 0;
	unsigned int i = 0;
	unsigned int numOfCards = 0;

	//Seed rand with current time in seconds.
	srand((int)time(0));

	if (0 == splitsParam)
	{
		numOfSplits = (rand() % (toSplit.deckSize)) + 1; // 1 - n
	}
	else 
	{
		if (splitsParam < 0)
		{
			std::cout << ">>>ERROR negative number" << std::endl << std::endl;			//FIX, END PROGRAM
		}

		//To avoid unnecessary spliting that could go on for a very long time.
		if (splitsParam >= toSplit.deckSize)
		{
			std::cout << "Split Parameter > deckSize" << std::endl;
			splitsParam = toSplit.deckSize - 1;
		}

		numOfSplits = splitsParam;
	}
	

	//New array holding cut Deck
	CardDeck::card * splitDeck = new CardDeck::card[toSplit.deckSize];

	if (toSplit.deckSize > 1)
	{
		while (numOfSplits > 0)
		{		
			//Reset values for the start of loop through deck bc number of splits hasn't been met.
			i = 0;
			numOfCards = toSplit.deckSize;
			randPivotCard = 0;

			while (numOfCards > 1 && numOfSplits > 0)
			{
				//Card to pivot around
				randPivotCard = (rand() % (numOfCards - 1)) + 1 + randPivotCard;	// 1 - deckSize-2				

				for (i; i < randPivotCard; i++)
				{
					splitDeck[numOfCards - (randPivotCard - i)] = toSplit.arrDeck[i];
				}

				numOfCards = toSplit.deckSize - i; 
				numOfSplits--;
			}

			//Fill in deck with cards that weren't split
			for(i; i < toSplit.deckSize; i++)
				splitDeck[i - randPivotCard] = toSplit.arrDeck[i];

			//Copy split deck values into cardDeck class arrDeck
			toSplit.copyDeck(splitDeck);
		}
	}

	delete[] splitDeck;
}
void DeckShuffle::zipperShuffle(CardDeck & toZip)
{
	//Seed rand with current time in seconds.
	srand((int)time(0));
	int random;

	CardDeck::card * zipperDeck = new CardDeck::card[toZip.deckSize];
	unsigned int halfDeck = toZip.deckSize / 2;
	unsigned int i = 0, j = 0;

	//Loop should go through all one half of the deck, smallest one, zippering those cards that
	//make it and just adding the rest that didn't make it into the back of the deck.
	for (unsigned int k = 0; k < toZip.deckSize; k++)
	{
		//Deck still needs to be zippered if this if statement is true
		if ( i < halfDeck && (halfDeck + j) < toZip.deckSize)
		{
			//Call random in loop
			random = (rand() % 8) + 1;
			//std::cout << "Random #" << i << ":" << j << " : "<< random << std::endl;

			zipperDeck[k] = toZip.arrDeck[i];
			// 7/8 chance to zipper
			if (random < 8)
			{
				zipperDeck[k + 1] = toZip.arrDeck[halfDeck + j];
				j++;
				k++;
			}
			i++;
		}
		// i - halfDeck needs to be added to the back of the new zippered deck.
		else if (i < halfDeck)
		{
			zipperDeck[k] = toZip.arrDeck[i];
			i++;
		}
		// halfDeck - deckSize needs to be added to the back of the new deck.
		else if ((halfDeck + j) < toZip.deckSize)
		{
			zipperDeck[k] = toZip.arrDeck[halfDeck + j];
			j++;
		}
		// ELSE there was a problem, so show this with a -1
		else
		{
			//zipperDeck[k] = -1;												//FIX!!!!
		}
	}

	if (toZip.deckSize > 0)
	{
		//Make zippered deck copy to old deck
		toZip.copyDeck(zipperDeck);
	}

	delete[] zipperDeck;
}