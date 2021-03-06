#include "CardDeck.h"

namespace CARDDECK
{
	//Construct CardDeck with parameter passed or default value of 0 which defines the type of card game to be used;
	//explicit needed because constructor has only one parameter and so to avoid assignments of non objects to
	//this object.
	CardDeck::CardDeck(unsigned int decks)
	{
		//numOfDecks should never be less than 1 with this condition
		if (decks > 0)
		{	numOfDecks = decks;}
		else
		{	numOfDecks = 1;}
		vectorDeck.resize(STD_DECK_SIZE * numOfDecks);
		totalCards = STD_DECK_SIZE * numOfDecks;
		createPlayingCards();
	}

	//Default constructor creates a 0 card deck/ an error to be caught later;
	CardDeck::CardDeck()
	{
		vectorDeck.resize(0);
		numOfDecks = 0;
		totalCards = 0;
	}

	//Create cards for a typical playing card deck, ex: Ace, King, Queen, Jack, ... etc.
	//For use only by the standard 52 card deck.
	void CardDeck::createPlayingCards()
	{
		
		//List ADT from which random card order will come from.
		std::list <unsigned int> randomDeck;
		std::list <unsigned int>::iterator it1;

		//Loop populates list with unsigned ints from 0 - totalCards - 1 for next step.
		for (unsigned int cardNumber = 0; totalCards > cardNumber; cardNumber++)
		{
			randomDeck.push_back(cardNumber);
		}

		unsigned int randomNumber = 0;
		unsigned int currIndex = 0;

		
		//Loop 
		for (unsigned int maxCard = totalCards; maxCard > 1; maxCard--)
		{

			//Seed rand with current time in seconds.
			srand((int)time(0));
			//Random number from 0 - maxCard-1.
			randomNumber = (rand() % maxCard); // 0 - maxCard-1

			//Reset iterator to beginning.
			it1 = randomDeck.begin();
			//Advance iterator to random number.
			std::advance(it1, randomNumber);

			//Fill vectorDeck at currIndex with the value of the randomly selected iterator it1;
			//this includes a deck number, suit, and card value. This makes each card unique 
			//and identifiable to the program.
			vectorDeck[currIndex].resize(3);
			vectorDeck[currIndex][0] = *it1 / 52;
			vectorDeck[currIndex][1] = (*it1 % 52) / 13;
			vectorDeck[currIndex][2] = *it1 % 13;
			currIndex++;

			//Erase this value from list ADT.
			randomDeck.erase(it1);
		}

		//Fill in the last currIndex; THIS COULD BE DONE BETTER, THE PROBLEM IS THE REPITITION OF CODE.
		//Reset iterator for the last time.
		it1 = randomDeck.begin();
		//Set last vector index to proper value.
		vectorDeck[currIndex].resize(3);
		vectorDeck[currIndex][0] = *it1 / 52;
		vectorDeck[currIndex][1] = (*it1 % 52) / 13;
		vectorDeck[currIndex][2] = *it1 % 13;

		/*
		//Fill vectorDeck with the values of their deck number, suit, and card value. This makes each card unique and 
		//identifiable to the program.
		for (unsigned int cardIndex = 0; cardIndex < vectorDeck.size(); cardIndex++)
		{
			vectorDeck[cardIndex].resize(3);
			vectorDeck[cardIndex][0] = cardIndex / 52;
			vectorDeck[cardIndex][1] = (cardIndex % 52) / 13;
			vectorDeck[cardIndex][2] = cardIndex % 13;
		}
		*/
		return;
	}

	//Prints out playing card deck based on first - last; i.e. 0 - deckSize-1.
	//For universal use by playing card decks of any size, not just the standard 52 card deck.
	void CardDeck::printDeck() const
	{
		if (0 == vectorDeck.size())
		{
			std::cout << "Zero cards in deck." << std::endl;
		}
		else
		{
			std::cout << "[ " << vectorDeck[0][0] << ":" << vectorDeck[0][1] << vectorDeck[0][2];
			for (unsigned int i = 1; i < vectorDeck.size(); i++)
			{
				std::cout << ", " << vectorDeck[i][0] << ":" << vectorDeck[i][1] << vectorDeck[i][2];
			}
			std::cout << " ]" << std::endl << std::endl;
		}
		return;
	}
}
