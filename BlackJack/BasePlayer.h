#ifndef BasePlayer_H
#define BasePlayer_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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


namespace BASEPLAYER
{
	class BasePlayer
	{
	private:

		unsigned int ai;
		unsigned int playerNumber;
		unsigned int draws;
		unsigned int losses;
		unsigned int wins;

	public:
		BasePlayer(unsigned int playerType = 0);
		virtual ~BasePlayer();

		//GETTERS
		unsigned int getDraws() const { return draws; }						//Inline function
		unsigned int getLosses() const { return losses; }					//Inline function
		unsigned int getWins() const { return wins; }						//Inline function
		unsigned int getPlayerNum() const { return playerNumber; }			//Inline function

		virtual void playerReset() = 0;

		//SETTERS
		void setDraws() { draws += 1; }										//Inline function
		void setLosses() { losses += 1; }									//Inline function
		void setWins() { wins += 1; }										//Inline function
		void setPlayerNum(unsigned int number) { playerNumber = number; }	//Inline function
	};
}

#endif // !BasePlayer_H