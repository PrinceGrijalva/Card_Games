#include "BasePlayer.h"

namespace BASEPLAYER
{
	//Default constructs a player object set to either AI or user player type
	BasePlayer::BasePlayer(unsigned int playerType)
	{
		ai = playerType;
		playerNumber = 0;
		draws = 0;
		losses = 0;
		wins = 0;
	}

	BasePlayer::~BasePlayer()
	{
		//std::cout  << "Called BasePlayer DESTRUCTOR" << std::endl << std::endl;
	}

	//Resets the hands of the player so they can start again fresh   
	void BasePlayer::playerReset()
	{
		//Blank
	}
}