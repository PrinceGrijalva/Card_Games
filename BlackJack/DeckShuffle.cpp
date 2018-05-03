#include "DeckShuffle.h"

namespace DECKSHUFFLE
{
	//Constructor; cardDeck to point to data of deck for use in the DeckShuffle function
	DeckShuffle::DeckShuffle(CARDDECK::CardDeck & deck)
	{
		//This is an error flag for use in BlackJack class
		deckShuffleError = 0;
		if (0 == deck.getTotalCards())
		{
			std::cout << "cardDeck ERROR: cardDeck == NULL" << std::endl;
			//Set error flag so program does not continue as normal
			deckShuffleError = 1;
		}
		else
		{
			VALIDINPUT::ValidInput validate;

			//cardDeck = address of deck; cardDeck is a ptr to CardDeck
			cardDeck = deck.getVectorDeck();
			cardSize = cardDeck->size();

			std::cout << "Would you like to shuffle the deck?  Y/N" << std::endl;

			if (validate.validStrYesNo())
			{
				shuffleDeck();
			}
			else
			{
				//Do not shuffle deck
			}
			//Print deck out to check that it's shuffled.
			//deck.printDeck();
		}
	}

	//Default Constructor
	DeckShuffle::DeckShuffle()
	{
		//Should not be using default constructor because there is no deck to shuffle
		//and error set to 1
		deckShuffleError = 1;
	}

	//Shuffle a deck that is being used by using functions in this class
	void DeckShuffle::shuffleDeck()
	{
		splitDeck();
		zipperShuffle();
		splitDeck();
		zipperShuffle();
		zipperShuffle();
		splitDeck();
		zipperShuffle();
		splitDeck();
		return;
	}

	//SHUFFLE technique: cut the deck based on a random number. 
	/* FOR THIS FUNC MIGHT BE A BETTER IDEA TO USE A DATA STRUCTURE LIKE QUEUE
	*IF USING A LARGE DATA SET; AVG CASE LOOKS BETTER*/

	//Pick a random card from the deck at any position except the first one, random = 1 - n-1;
	//		>Break cards into two groups, every card < random number and every card a >= random number.
	//		>Move 1st group to the rhs of all of the 2nd group. Emulates cutting the cards down a pivot.
	//		>Can do multiple successive cuts if asked but won't do more than size of deck cuts.
	//		>Can cut the lhs by doing the process over again as long as the number of cards remaining
	//		is > 1. Any splits left over not made by the above process go on to split the whole deck
	//		repeating the process.
	// COMPLETED AND WORKS------------------------------------------------------------------------------------
	void DeckShuffle::splitDeck(unsigned int splitsParam)
	{
		//Always initialize variables in c++
		unsigned int numOfSplits = 0;			//How many deck splits
		unsigned int randPivotCard = 0;			//Where to split the deck in two
		unsigned int i = 0;						//Iterator variable
		unsigned int numOfCards = 0;			//Number of cards left to split after a successful split

		//Seed rand with current time in seconds.
		srand((int)time(0));

		if (splitsParam < 0)
		{
			std::cout << "splitsParam ERROR: negative number" << std::endl << std::endl;
			splitsParam = 0;
			deckShuffleError = 1;
		}
		else if (0 == splitsParam)
		{
			//Random number of splits from 1 - n-1
			numOfSplits = (rand() % (cardSize - 1)) + 1; // 1 - n-1
		}
		else
		{
			//To avoid unnecessary spliting that could go on for a very long time.
			if (splitsParam >= cardSize)
			{
				std::cout << "Split Parameter > cardSize" << std::endl;
				splitsParam = cardSize - 1;  //n-1 cuts
			}

			numOfSplits = splitsParam;
		}

		//Contine if cardSize is managable and there are no errors from splitParam; 0 case is handled by constructor
		if (cardSize > 1 && 0 == deckShuffleError)
		{
			//New vector holding split Deck intialized to all 0s
			std::vector< std::vector <unsigned int> > splitDeck(cardSize, std::vector<unsigned int>(3, 0));

			while (numOfSplits > 0)
			{
				//Reset values for the start of loop through deck b/c number of splits hasn't been met.
				i = 0;
				numOfCards = cardSize;
				randPivotCard = 0;

				while (numOfCards > 1 && numOfSplits > 0)
				{
					//Card to pivot around
					randPivotCard = (rand() % (numOfCards - 1)) + 1 + randPivotCard;	// 1 <-> cardSize-1			

					for (i; i < randPivotCard; i++)
					{
						splitDeck[numOfCards - (randPivotCard - i)] = (*cardDeck)[i];
					}

					numOfCards = cardSize - i;
					numOfSplits--;
				}

				//Fill in deck with cards that weren't split
				for (i; i < cardSize; i++)
				{
					splitDeck[i - randPivotCard] = (*cardDeck)[i];
				}

				//Copy split deck values into cardDeck variable vectorDeck used in rest of program
				(*cardDeck) = splitDeck;
			}
		}
		return;
	}

	//SHUFFLE technique: zipper the two halfs of the deck together. 

	//Start by spliting deck in half, or close to it, and then sequentially go down both halves:
	//		> 1st half next card into zipper vector
	//		> Chance for 2nd half next card into zipper vector
	//		> Go back to first step if 1st half still has cards.
	//		> Include the rest of 2nd half into zipper deck and finish.
	//The above should simulate a zippering shuffle of cards done on physical cards.
	//COMPLETED AND WORKS---------------------------------------------------------------------------
	void DeckShuffle::zipperShuffle()
	{
		//Seed rand with current time in seconds.
		srand((int)time(0));
		int random = 0;

		//This case is bad and shuffle should not continue; 0 case is handled by constructor
		if (1 == cardSize)
		{
			//Do Nothing, just exit since this shuffle is impossible
		}
		//This case is good and shuffle should continue
		else if (cardSize > 1)
		{
			std::vector< std::vector <unsigned int> > zipperDeck(cardSize, std::vector<unsigned int>(3, 0));
			std::vector <unsigned int> errorCard(3, -1);

			unsigned int halfDeck = cardSize / 2;
			unsigned int i = 0, j = 0;

			//Loop should go through all one half of the deck, smallest one, zippering those cards that
			//make it and just adding the rest that didn't make it into the back of the deck.
			for (unsigned int k = 0; k < cardSize; k++)
			{
				//Deck still needs to be zippered if true
				if (i < halfDeck && (halfDeck + j) < cardSize)
				{
					//Call random in loop
					random = (rand() % 20) + 1;
					//std::cout << "Random #" << i << ":" << j << " : "<< random << std::endl;

					zipperDeck[k] = (*cardDeck)[i];						//Insert 1st half card into zipperDeck
					// 19/20 chance to zipper
					if (random < 20)
					{
						zipperDeck[k + 1] = (*cardDeck)[halfDeck + j];	//Insert 2nd half card into zipperDeck
						j++;
						k++;
					}
					i++;
				}
				// i - halfDeck needs to be added to the back of the new zippered deck.
				else if (i < halfDeck)
				{
					zipperDeck[k] = (*cardDeck)[i];
					i++;
				}
				// halfDeck - cardSize needs to be added to the back of the new deck.
				else if ((halfDeck + j) < cardSize)
				{
					zipperDeck[k] = (*cardDeck)[halfDeck + j];
					j++;
				}
				// ELSE there was a problem, so show this with a -1, can be checked
				else
				{
					std::cout << std::endl << "ERROR in for loop of zipperShuffle" << std::endl;
					zipperDeck[k] = errorCard;
					deckShuffleError = 1;
				}
			}

			//Make zippered deck copy to the deck used in rest of program.
			(*cardDeck) = zipperDeck;
		}
		return;
	}
}