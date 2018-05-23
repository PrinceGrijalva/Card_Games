#ifndef BJPlayer_H
#define BJPlayer_H

#include "BasePlayer.h"

namespace BJPLAYER
{
	class BJPlayer : public BASEPLAYER::BasePlayer
	{
	private:
		std::vector< std::vector <unsigned int> > handOne;
		std::vector< std::vector <unsigned int> > handTwo;

		unsigned int handOneSum;
		unsigned int handTwoSum;
		unsigned int howManyAces;
		bool natural;

		void countCard();

	public:
		BJPlayer(unsigned int playerType = 0);

		//GETTERS
		bool getNatural() const { return natural; }							//Inline function

		void insertCardToHand(std::vector <unsigned int> newCard, unsigned int whichHand = 0);
		virtual void playerReset();
		void printHand(unsigned int whichHand = 0, unsigned int aiOrNot = 0) const;
		//SETTERS
		void setNatural() { natural = true; }								//Inline function

		unsigned int returnSum() const;
		unsigned int returnThatCard(unsigned int i, unsigned int whichHand = 0) const;
	};
}

#endif // !BJPlayer_H