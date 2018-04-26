#include "BlackJack.h"

//Construct the game black jack -> Create cards , Play game;
BlackJack::BlackJack()
{
	//INITIALIZATION------------------------------
	errorBlackJack = false;
	std::string gameInput = "";
	unsigned int gameNumber = 0;
	bool gameContinue = true;
	bool valid = false;
	VALIDINPUT::ValidInput validate;

	std::cout << std::endl << "Welcome to BlackJack!" << std::endl << std::endl;

	//USER_INPUT1---------------------------------
	std::cout << "Would you like there to be 1 deck or 4 decks?" << std::endl;

	while (true)
	{
		//This can be opened up to include any number of decks; would suggest at most a 2 digit number of decks
		//Would need to use:  validate.validIntInput(gameNumber,2);
		//Check for 0 may be necessary if including any number of user defined decks.
		std::cout << "Please enter 1 or 4: " << std::endl;
		if (validate.validIntInput(gameNumber, 4))
		{
			//Use user input to create the proper deck object
			if (0 == gameNumber)
			{
				std::cout << "Cannot have 0 decks. Enter a different 2 digit number." << std::endl 
					<< std::endl;
			}
			else if (1 == gameNumber)
			{
				deck = CARDDECK::CardDeck(gameNumber);
				break;
			}
			else if (4 == gameNumber)
			{
				deck = CARDDECK::CardDeck(gameNumber);
				break;
			}
			else
			{
				std::cout << "Not an acceptable number. Try again." << std::endl << std::endl;
			}
		}
	}

	//This shuffle is needed to shuffle a deck using more than 52 cards.
	DECKSHUFFLE::DeckShuffle prep(deck);
	//Sets up the current card to look at as 0 in vector.
	currentCard = 0;
	//Initialize cardDeck as the vector of vectors of unsigned ints
	cardDeck = deck.getVectorDeck();


	//EDIT below when two or more players will be used ----------------------------///////////////////////
	//Will probably need to use new; dynamic memory
	Player player1;
	playerList.push_back(player1);
	Player dealer(1);
	playerList.push_back(dealer);
	unsigned int j = 0;

	//GAME BEGINS---------------------------------
	//Game continues as long as player wishes it to and there wasn't an error
	while (gameContinue == true && 0 == prep.returnError())
	{
		//Reset these values everytime a new game starts
		unsigned int playersBusted = 0;
		dealerContinue = true;
		highestPlayerHand = 0;
		playerNatural = 0;

		//deck->printDeck();

		//Deal cards to every player and print them out.
		//Maybe only print out dealers hand------------------------------------------!!!!!
		for (j = 0; j < playerList.size(); j++)
		{
			//Insert cards into a players hand to be able to track them
			playerList[j].insertCardToHand((*cardDeck)[currentCard]);
			playerList[j].insertCardToHand((*cardDeck)[currentCard + 1]);

			if (playerList.size() - 1 == j)
			{
				//Print out the cards dealt to the dealer.
				std::cout << "DEALER's HAND: " << std::endl;
				playerList[j].printHand(0, 1);
			}
			else
			{
				//Set player number
				playerList[j].setPlayerNum(j + 1);
				//Print out the cards dealt to player or ai player	.	
				//std::cout << "PLAYER " << j + 1 << "'s HAND: " << std::endl;
				//playerList[j].printHand(0, 0);
			}
			std::cout << std::endl;
			//Increment currentCard to reflect the two dealt cards.
			currentCard += 2;
		}

		std::cout << "-------------------------------------------" << std::endl << std::endl;

		//Let player(s) go first then the dealer goes
		for (j = 0; j < playerList.size(); j++)
		{
			//Dealer's turn
			if (playerList.size() - 1 == j)
			{
				if ( (playersBusted == playerList.size() - 1 || playerNatural == playerList.size() - 1 )
					&& playerList.size() > 1)
				{
					dealerContinue = false;
				}
				dealerTurn(playerList[j], currentCard);

				std::cout << "DEALER TOTAL: ";
			}
			//Player's turn
			else
			{
				yourTurn(playerList[j], currentCard);
				if (playerList[j].returnSum() > 21)
				{
					playersBusted += 1;
				}
				else if (highestPlayerHand < playerList[j].returnSum())
				{
					highestPlayerHand = playerList[j].returnSum();
				}
				else
				{
					//NOTHING
				}
				std::cout << "PLAYER" << j + 1 << " TOTAL: ";

				//Check if player has got a natural
				if (playerList[j].getNatural())
				{
					playerNatural += 1;
				}
			}

			//Let the player(s) know their total(s)
			if (21 == playerList[j].returnSum())
			{
				if (playerList[j].getNatural())
				{
					std::cout << "NATURAL BLACKJACK" << std::endl << std::endl;
				}
				else
				{
					std::cout << "SOFT BLACKJACK" << std::endl << std::endl;
				}
			}
			else if (21 < playerList[j].returnSum())
			{
				std::cout << "BUST" << std::endl << std::endl;
			}
			else
			{
				std::cout << playerList[j].returnSum() << std::endl << std::endl;
			}
		}

		//The dealer's sum that needs to be checked and if the dealer got a natural
		unsigned int dealerSum = playerList[playerList.size() - 1].returnSum();
		bool dealerNatural = playerList[playerList.size() - 1].getNatural();

		//Check the users against the dealer and determine if they win or lose
		for (j = 0; j < playerList.size() - 1; j++)
		{
			//In this case the user will always lose as they have busted;gone over 21
			if (playerList[j].returnSum() > 21)
			{
				std::cout << "DEALER WINS over PLAYER" << j + 1 << std::endl;
				playerList[j].setLosses();
			}
			//In this case the user will 2/3 win or 1/3 draw with the dealer
			else if (21 == playerList[j].returnSum())
			{
				if (playerList[j].getNatural())
				{
					if (dealerNatural)
					{
						std::cout << "PLAYER" << j + 1 << " DRAWS with DEALER" << std::endl;
						playerList[j].setDraws();
					}
					else
					{
						std::cout << "PLAYER" << j + 1 << " WINS over DEALER" << std::endl;
						playerList[j].setWins();
					}
				}
				else
				{
					if (21 == dealerSum)
					{
						std::cout << "PLAYER" << j + 1 << " DRAWS with DEALER" << std::endl;
						playerList[j].setDraws();
					}
					else
					{
						std::cout << "PLAYER" << j + 1 << " WINS over DEALER" << std::endl;
						playerList[j].setWins();
					}
				}
			}
			else
			{
				if (dealerSum > 21 || playerList[j].returnSum() > dealerSum)
				{
					std::cout << "PLAYER" << j + 1 << " WINS over DEALER" << std::endl;
					playerList[j].setWins();
				}
				else if (playerList[j].returnSum() == dealerSum)
				{
					std::cout << "PLAYER" << j + 1 << " DRAWS with DEALER" << std::endl;
					playerList[j].setDraws();
				}
				//playerSum < dealerSum---------------------------------//////////////maybe error?
				else
				{
					std::cout << "DEALER WINS over PLAYER" << j + 1 << std::endl;
					playerList[j].setLosses();
				}
			}
			//All players should be reset
			playerList[j].playerReset();
		}

		//Reset the dealer as well, previously missed this step!
		playerList[playerList.size() - 1].playerReset();

		//USER_INPUT3------------------------------
		//Play Again?
		while (true)
		{
			std::cout << std::endl;
			//Reset userInput just in case
			bool answer = true;
			std::cout << "Play Again?  Enter y or n: " << std::endl;
			answer = validate.validStrYesNo();
			if (answer)
			{
				gameContinue = true;
				//If there is one deck or when using 4 decks and only 52 cards remain reshuffle the
				//whole lot of cards. The choice of less than 52 cards remaining is arbitrary;
				//can be changed.
				if (52 == deck.getTotalCards() || currentCard > deck.getTotalCards() - 52)
				{
					currentCard = 0;
					prep.shuffleDeck();
					//deck.printDeck();
				}
				break;
			}
			else 
			{
				gameContinue = false;
				break;
			}
		}
	}

	if (0 == deck.getTotalCards())
	{
		std::cout << "deckOfCards ERROR; deckOfCards is 0" << std::endl;
		errorBlackJack = true;
	}
	else if (1 == prep.returnError())
	{
		errorBlackJack = true;
	}
	else
	{
		//FINAL SCORE-----------------------------------
		for (j = 0; j < playerList.size() - 1; j++)
		{
			std::cout << std::endl << "PLAYER" << j + 1 << " Win:" << playerList[j].getWins()
				<< " Lose:" << playerList[j].getLosses() << " Draw:"
				<< playerList[j].getDraws() << std::endl;
		}
		std::cout << "-------------------------------------------" << std::endl << std::endl;
	}
}

BlackJack::~BlackJack()
{
	//std::cout  << "Called DESTRUCTOR" << std::endl << std::endl;
}

void BlackJack::dealerTurn(Player & dealer, unsigned int & currentCard)
{
	unsigned int cardHit = 0;

	std::cout << "DEALER's TURN:" << std::endl;
	dealer.printHand();

	//Set that the dealer got a natural 21
	if (21 == dealer.returnSum())
	{
		dealer.setNatural();
	}

	//Dealer must contine until at least 17 is reached
	//This loop must not be done if all players are busted as there is no point for the dealer to continue
	//This loop must not be done if no player has a higher hand than the dealers default hand
	while (dealer.returnSum() < 17 && dealerContinue && dealer.returnSum() < highestPlayerHand)
	{
		dealer.insertCardToHand((*cardDeck)[currentCard]);

		currentCard += 1;
		dealer.printHand();
	}
}

void BlackJack::yourTurn(Player & currentPlayer, unsigned int & currentCard)
{
	unsigned int userInput = 0;

	std::cout << "PLAYER" << currentPlayer.getPlayerNum() << "'s TURN:" << std::endl;
	currentPlayer.printHand();

	//Hit your hand, use currentCard here
	unsigned int cardHit = 0;

	VALIDINPUT::ValidInput validate;
	bool answer = true;

	//Set that the player got a natural 21
	if (21 == currentPlayer.returnSum())
	{
		currentPlayer.setNatural();
	}

	//USER_INPUT2-------------------------
	while (answer && currentPlayer.returnSum() < 21)
	{
		//Reset userInput just in case
		//answer = "";
		std::cout << "Hit?  Enter y or n: " << std::endl;
		answer = validate.validStrYesNo();
		if (answer)
		{
			//std::cout << "DEALER: " << std::endl << "[" << values[deck.vectorDeck[x][2]] << " of "
			//	<< suits[deck.vectorDeck[x][1]] << "] ";

			currentPlayer.insertCardToHand((*cardDeck)[currentCard]);
			
			currentCard += 1;
			currentPlayer.printHand();
		}
		//std::cout << std::endl << "Current Player total: " << currentPlayer.returnSum() << std::endl;
	}
}