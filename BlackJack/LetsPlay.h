#pragma once

#include "BlackJack.h"

/*
* This class serves the purpose of being the spring board into other game classes based on the 
* user's selection. Will include many playing card games or other types of card games.
*/
namespace
{
	const std::vector <std::string> gameList = { "Quit","BlackJack","Poker","War" };
}


namespace LETSPLAY
{
	class LetsPlay
	{
	private:
	public:
		LetsPlay();
	};
}

//#endif // !LetsPlay_H