#include "Player.h"

//Construct a player object set to either AI or user player type
//explicit necessary because constructor only has one parameter.
Player::Player(unsigned int playerType) : ai(playerType)
{	
	natural = false;
	draws = 0;
	losses = 0;
	wins = 0;
	handOneSum = 0;
	handTwoSum = 0;
	playerClassError = 0;
}

//Add new card value to running sum of all cards in current hand.
void Player::countCard()
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
	//There was an error
	else
	{
		playerClassError = 1;
		std::cout << "ERROR in countCard:" << handOne[handOne.size() - 1][2]
			<< " card value is beyond 0 - 12" << std::endl << std::endl;
	}

	//Change the value of an ace if exists and will set hand sum to be over 21
	while (handOneSum > 21 && howManyAces > 0)
	{
		handOneSum -= 10;
		howManyAces -= 1;
	}
	return;
}

//A whole bunch of Getters below whose uses are self evident

//Insert card into hand which is a vector of vectors and then call another function to count it in 
//hand sum.
void Player::insertCardToHand(std::vector <unsigned int> newCard, unsigned int whichHand)
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
			std::cout << "Something wrong happened while inserting card into hand.";
		}
	}
	return;
}

//Resets the hands of the player so they can start again fresh   
void Player::playerReset()
{
	howManyAces = 0;
	natural = false;
	handOneSum = 0;
	handTwoSum = 0;
	handOne.clear();
	handTwo.clear();
	playerClassError = 0;
	return;
}

//Print out hand of player taking into consideration if the player is the dealer.
void Player::printHand(unsigned int whichHand, unsigned int aiOrNot) const
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
		playerClassError = 1;
		std::cout << "Something went wrong when printing out this hand." << std::endl;
	}
	std::cout << std::endl;
	return;
}

//Getter; returns the sum of a hand
unsigned int Player::returnSum() const
{ 
	return handOneSum; 
}

//Getter; returns a card
unsigned int Player::returnThatCard(unsigned int i, unsigned int whichHand) const
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
		playerClassError = 1;
		std::cout << "Something wrong happened when returning that card.";
		return 0;
	}
}