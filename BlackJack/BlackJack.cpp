#include "BlackJack.h"

//Default Constructor of the game black jack -> Create cards ,Shuffle Cards, Play game;
BlackJack::BlackJack()
{
	//INITIALIZATION------------------------------
	dealerSum = 0;
	errorBlackJack = false;
	playersBusted = 0;
	currentPlayerSum = 0;
	unsigned int numOfDecks = 0;
	bool gameContinue = true;
	unsigned int j = 0;
	VALIDINPUT::ValidInput validate;

	std::cout << std::endl << "Welcome to BlackJack!" << std::endl << std::endl;
	std::cout << "Would you like there to be 1 deck or 4 decks?" << std::endl;

	while (true)
	{
		//This can be opened up to include any number of decks; would suggest at most a 2 digit number of decks
		//Would need to use:  validate.validIntInput(gameNumber,2);
		//Check for 0 may be necessary if including any number of user defined decks.
		std::cout << "Please enter 1 or 4: " << std::endl;
		//USER_INPUT1---------------------------------
		if (validate.validIntInput(numOfDecks, 4))
		{
			//Use user input to create the proper deck object
			if (0 == numOfDecks)
			{
				std::cout << "Cannot have 0 decks. Enter a different 2 digit number." << std::endl 
					<< std::endl;
			}
			else if (1 == numOfDecks)
			{
				deck = CARDDECK::CardDeck(numOfDecks);
				break;
			}
			else if (4 == numOfDecks)
			{
				deck = CARDDECK::CardDeck(numOfDecks);
				break;
			}
			else
			{
				std::cout << "Not an acceptable number. Try again." << std::endl << std::endl;
			}
		}
	}

	//This calls the Deckshuffle class to shuffle the cards 
	DECKSHUFFLE::DeckShuffle prep(deck);
	//Sets up the current card to look at as 0 in vector.
	currentCard = 0;
	//Initialize cardDeck as the vector of vectors of unsigned ints for easier access
	//Normally the vector of vectors of unsigned ints is a private variable of the CardDeck class.
	cardDeck = deck.getVectorDeck();


	//EDIT below when two or more players will be used ----------------------------///////////////////////
	//Will probably need to use new; dynamic memory
	BJPlayer player1;
	playerList.push_back(player1);
	BJPlayer dealer(1);
	playerList.push_back(dealer);

	//GAME BEGINS---------------------------------
	//Game continues as long as player wishes it to and there wasn't an error
	while (gameContinue == true && 0 == prep.returnError())
	{
		//Reset these values everytime a new game starts
		playersBusted = 0;
		dealerContinue = true;
		highestPlayerHand = 0;
		playerHit21 = 0;


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
				if ( (playersBusted == playerList.size() - 1 || playerHit21 == playerList.size() - 1 )
					&& playerList.size() > 1)
				{
					dealerContinue = false;
				}
				dealerTurn(playerList[j], currentCard);
				currentPlayerSum = playerList[j].returnSum();

				std::cout << "DEALER TOTAL: ";
			}
			//Player's turn
			else
			{
				yourTurn(playerList[j], currentCard);
				currentPlayerSum = playerList[j].returnSum();
				if (currentPlayerSum > 21)
				{
					playersBusted += 1;
				}
				else if (highestPlayerHand < currentPlayerSum)
				{
					highestPlayerHand = currentPlayerSum;
				}
				else
				{
					//NOTHING
				}
				std::cout << "PLAYER" << j + 1 << " TOTAL: ";

				//Check if player has got a natural
				if (playerList[j].getNatural() || 21 == currentPlayerSum)
				{
					playerHit21 += 1;
				}
			}

			//Let the player(s) and dealer know their total(s)
			if (21 == currentPlayerSum)
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
			else if (21 < currentPlayerSum)
			{
				std::cout << currentPlayerSum << " - BUST" << std::endl << std::endl;
			}
			else
			{
				std::cout << currentPlayerSum << std::endl << std::endl;
			}
		}

		//Set the dealer's sum to be checked against player's sums
		dealerSum = playerList[playerList.size() - 1].returnSum();

		//Check the users against the dealer and determine if they win or lose
		for (j = 0; j < playerList.size() - 1; j++)
		{
			//Set player hand sum once and check it multiple times.
			currentPlayerSum = playerList[j].returnSum();
			//In this case the user will always lose as they have busted;gone over 21
			if (currentPlayerSum > 21)
			{
				std::cout << "DEALER WINS over PLAYER" << j + 1 << std::endl;
				playerList[j].setLosses();
			}
			//In this case the user can win or draw with dealer
			else if (21 == currentPlayerSum)
			{
				if (playerList[j].getNatural())
				{
					std::cout << "PLAYER" << j + 1 << "'S NATURAL WINS over DEALER" << std::endl;
					playerList[j].setWins();
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
			//In this case the player can win, draw, or lose to dealer
			else
			{
				if (dealerSum > 21 || currentPlayerSum > dealerSum)
				{
					std::cout << "PLAYER" << j + 1 << " WINS over DEALER" << std::endl;
					playerList[j].setWins();
				}
				else if (currentPlayerSum == dealerSum)
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
			//All human players should be reset
			playerList[j].playerReset();
		}

		//Reset the dealer as well, previously missed this step!
		playerList[playerList.size() - 1].playerReset();

		//Play Again?
		std::cout << std::endl;
		//Reset userInput just in case
		bool answer = true;
		std::cout << "Play Again?  Enter y or n: " << std::endl;
		//USER_INPUT3------------------------------
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
			}
		}
		else 
		{
			gameContinue = false;
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
	//std::cout  << "Called BlackJack DESTRUCTOR" << std::endl << std::endl;
}

//Dealer's turn to hit or stand based on certain rules
void BlackJack::dealerTurn(BJPlayer & dealer, unsigned int & currentCard)
{
	unsigned int dealerSum = dealer.returnSum();
	std::cout << "DEALER's TURN:" << std::endl;
	dealer.printHand();

	//Set that the dealer got a natural 21
	if (21 == dealerSum)
	{
		dealer.setNatural();
	}

	//Dealer must contine until at least 17 is reached
	//This loop must not be done if all players are busted as there is no point for the dealer to continue
	//This loop must not be done if no player has a higher hand than the dealers default hand
	//HAD FORGOTTEN TO SET LAST CHECK AS <=, had it set to <!!!!!!!
	while (dealerSum < 17 && dealerContinue && dealerSum <= highestPlayerHand)
	{
		dealer.insertCardToHand((*cardDeck)[currentCard]);
		currentCard += 1;
		dealer.printHand();
		dealerSum = dealer.returnSum();
	}
}

//Player's turn to hit or stand based on their input and sum
void BlackJack::yourTurn(BJPlayer & currentPlayer, unsigned int & currentCard)
{
	bool answer = true;
	unsigned int userInput = 0;
	unsigned int curPlayerSum = currentPlayer.returnSum();
	VALIDINPUT::ValidInput validate;

	std::cout << "PLAYER" << currentPlayer.getPlayerNum() << "'s TURN:" << std::endl;
	currentPlayer.printHand();

	//Set that the player got a natural 21
	if (21 == curPlayerSum)
	{
		currentPlayer.setNatural();
	}

	while (answer && curPlayerSum < 21)
	{
		//Reset userInput just in case
		//answer = "";
		std::cout << "Hit?  Enter y or n: " << std::endl;
		//USER_INPUT2-------------------------
		answer = validate.validStrYesNo();
		if (answer)
		{
			currentPlayer.insertCardToHand((*cardDeck)[currentCard]);	
			currentCard += 1;
			currentPlayer.printHand();
			curPlayerSum = currentPlayer.returnSum();
		}
		//std::cout << std::endl << "Current Player total: " << currentPlayer.returnSum() << std::endl;
	}
}