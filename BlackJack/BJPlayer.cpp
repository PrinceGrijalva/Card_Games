#include "BJPlayer.h"

namespace BJPLAYER
{
	//Default constructs a player object set to either AI or user player type
	BJPlayer::BJPlayer(unsigned int playerType) : BasePlayer(playerType)
	{
		natural = false;
		handOneSum = 0;
		handTwoSum = 0;
	}

	//Add new card value to running sum of all cards in current hand.
	void BJPlayer::countCard()
	{

		//Count Ace as 11 and count it in howManyAces variable to be possibly changed later
		if (12 == handOne[handOne.size() - 1][2])
		{
			handOneSum += 11;
			howManyAces += 1;
		}
		//Count 2 - 9 card values as face values
		else if (handOne[handOne.size() - 1][2] >= 0 && handOne[handOne.size() - 1][2] < 8)
		{
			handOneSum += (handOne[handOne.size() - 1][2] + 2);
		}
		//Count 10 - K card values as 10
		else if (handOne[handOne.size() - 1][2] > 7 && handOne[handOne.size() - 1][2] < 12)
		{
			handOneSum += 10;
		}
		//There was an error; this was build by help from Stack Overflow--
		//https://stackoverflow.com/questions/22753328/c-error-expression-must-have-integral-or-enum-type-getting-this-from-a-s
		else
		{
			std::ostringstream output;
			output << "BJPlayer > countCard() ERROR:" << handOne[handOne.size() - 1][2] <<
				" card value is beyond 0 - 12";
			std::string errorMsg = output.str();
			throw std::domain_error(errorMsg);
		}

		//Change the value of an ace if exists and will set hand sum to be over 21
		while (handOneSum > 21 && howManyAces > 0)
		{
			handOneSum -= 10;
			howManyAces -= 1;
		}
		return;
	}

	//Insert card into hand which is a vector of vectors and then call another function to count it in 
	//hand sum.
	void BJPlayer::insertCardToHand(std::vector <unsigned int> newCard, unsigned int whichHand)
	{
		//Check if newCard is blank or is wrong size then proceed to add to whichever hand
		if (!newCard.empty() && 3 == newCard.size())
		{
			if (0 == whichHand)
			{
				handOne.push_back(newCard);
				//Call function to count card in handOneSum
				countCard();
			}
			else if (1 == whichHand)
			{
				handTwo.push_back(newCard);
				//Call function to count card in handTwoSum - NOT YET FIXED TO WORK!!!!!!!!!!!--------------
				countCard();
			}
			else
			{
				std::ostringstream output;
				output << "BJPlayer > insertCardToHand() ERROR: Hand " 
					<< whichHand << " does not exist.";
				std::string errorMsg = output.str();
				throw std::domain_error(errorMsg);
			}
		}
		return;
	}

	//Resets the hands of the player so they can start again fresh   
	void BJPlayer::playerReset()
	{
		howManyAces = 0;
		natural = false;
		handOneSum = 0;
		handTwoSum = 0;
		handOne.clear();
		handTwo.clear();
		BasePlayer::playerReset();
		return;
	}

	//Print out hand of player taking into consideration if the player is the dealer.
	void BJPlayer::printHand(unsigned int whichHand, unsigned int aiOrNot) const
	{

		//std::cout << "handOne size: " << handOne.size() << std::endl;
		if (0 == whichHand)
		{
			for (unsigned int i = 0; i < handOne.size(); i++)
			{
				if (1 == aiOrNot && 1 == i)
				{
					std::cout << "[ Face Down ] ";
				}
				else
				{
					std::cout << "[" << values[handOne[i][2]] << " of "
						<< suits[handOne[i][1]] << "] ";
				}
			}

		}
		else if (1 == whichHand)
		{
			for (unsigned int i = 0; i < handTwo.size(); i++)
			{
				std::cout << "[" << values[handTwo[i][2]] << " of "
					<< suits[handTwo[i][1]] << "] ";
			}

		}
		else
		{
			std::ostringstream output;
			output << "BJPlayer > printHand() ERROR: Hand "
				<< whichHand << " does not exist.";
			std::string errorMsg = output.str();
			throw std::domain_error(errorMsg);
		}
		std::cout << std::endl;
		return;
	}

	//Getter; returns the sum of a hand
	unsigned int BJPlayer::returnSum() const
	{
		return handOneSum;
	}

	//Getter; returns a card
	unsigned int BJPlayer::returnThatCard(unsigned int i, unsigned int whichHand) const
	{
		if (0 == whichHand)
		{
			return handOne[i][2];
		}
		else if (1 == whichHand)
		{
			return handTwo[i][2];
		}
		else
		{
			std::ostringstream output;
			output << "BJPlayer > returnThatCard() ERROR: Hand "
				<< whichHand << " does not exist.";
			std::string errorMsg = output.str();
			throw std::domain_error(errorMsg);
		}
	}

	//Getter; returns the value of a card
	unsigned int BJPlayer::returnThatValue(unsigned int i, unsigned int whichHand) const
	{
		unsigned int value = 0;
		if (0 == whichHand)
		{
			value = handOne[i][2];
		}
		else if (1 == whichHand)
		{
			value = handTwo[i][2];
		}
		else
		{
			std::ostringstream output;
			output << "BJPlayer > returnThatCard() ERROR: Hand "
				<< whichHand << " does not exist.";
			std::string errorMsg = output.str();
			throw std::domain_error(errorMsg);
		}

		value += 2;
		if (value >= 10 && value <= 13)
		{
			value = 10;
		}
		else if (14 == value)
		{
			value = 11;
		}
		else
		{
			//Nothing
		}

		return value;
	}
}