#ifndef BlackJack_H
#define BlackJack_H

#include "CardDeck.h"
#include "DeckShuffle.h"
#include "BJPlayer.h"
#include "ValidInput.h"


/*
* This class serves the purpose of setting up a game of black jack. 
* > First ask how many 52 card decks should be combined to make up the black jack deck.
* > Create instance of class deckShuffle with deck as parameter.
* > Save pointer to vector of unsigned ints that is the deck for use in this class.
* > Possibly ask how many players / else one player and one dealer.
* > Start game by dealing out 2 cards to all players on playerList
* > Go to yourTurn function and based on values player can hit or stand
* > Go to dealerTurn function and dealer hits or stands to beat player 
* > Winner is determined and then declared.
* > Play again or not. 
* > Print final score(s).
*/

namespace BLACKJACK
{
	class BlackJack {
	private:
		bool dealerContinue;
		unsigned int currentCard;
		unsigned int currentPlayerSum;
		unsigned int dealerSum;
		unsigned int highestPlayerHand;
		unsigned int playersBusted;
		unsigned int playerHit21;

		CARDDECK::CardDeck deck;
		std::vector<BJPLAYER::BJPlayer> playerList;
		std::vector< std::vector <unsigned int> > * cardDeck;

		void dealerTurn(BJPLAYER::BJPlayer & dealer, unsigned int & currentCard);
		void yourTurn(BJPLAYER::BJPlayer & currentPlayer, unsigned int & currentCard);

	public:
		BlackJack();
		~BlackJack();
	};
}

#endif // !BlackJack_H