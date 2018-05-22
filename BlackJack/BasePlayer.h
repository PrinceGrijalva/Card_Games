#ifndef BasePlayer_H
#define BasePlayer_H

#include <iostream>
#include <vector>
#include <string>

/*
* BasePlayer class is meant to function as the paradigm for all player classes in any game which is to 
* be implemented in this group of games. The very first game this class works with is BlackJack and 
* can be expanded to work with more games. *A simplification may be necessary with a more specific
* BasePlayer class to be derived with inheritance from this base class for all games.
*/


namespace 
{
	const int SUITS_SIZE = 4;
	const int VALUES_SIZE = 13;
	//Constant 4 suits of a standard playing card deck. (INTERNAL LINKAGE)
	const std::string suits[SUITS_SIZE] = { "Spades", "Hearts", "Clubs", "Diamonds" };
	//Constant 13 values of a standard playing card deck. (INTERNAL LINKAGE)
	const std::string values[VALUES_SIZE] =
	{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
}


class BasePlayer
{
private:
	std::vector< std::vector <unsigned int> > handOne;
	std::vector< std::vector <unsigned int> > handTwo;

	unsigned int ai;
	mutable unsigned int playerClassError;
	unsigned int handOneSum;
	unsigned int handTwoSum;
	unsigned int howManyAces;
	unsigned int playerNumber;
	unsigned int draws;
	unsigned int losses;
	unsigned int wins;
	bool natural;

	void countCard();

public:
	BasePlayer(unsigned int playerType = 0);

	//GETTERS
	bool getNatural() const { return natural; }							//Inline function
	unsigned int getDraws() const { return draws; }						//Inline function
	unsigned int getLosses() const { return losses; }					//Inline function
	unsigned int getWins() const { return wins; }						//Inline function
	unsigned int getPlayerNum() const { return playerNumber; }			//Inline function

	void insertCardToHand(std::vector <unsigned int> newCard, unsigned int whichHand = 0);
	void playerReset();
	void printHand(unsigned int whichHand = 0, unsigned int aiOrNot = 0) const;
	//SETTERS
	void setNatural() { natural = true; }								//Inline function
	void setDraws() { draws += 1; }										//Inline function
	void setLosses() { losses += 1; }									//Inline function
	void setWins() { wins += 1; }										//Inline function
	void setPlayerNum(unsigned int number) { playerNumber = number; }	//Inline function

	unsigned int returnSum() const;
	unsigned int returnThatCard(unsigned int i, unsigned int whichHand = 0) const;
};

#endif // !BasePlayer_H