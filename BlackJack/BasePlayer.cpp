#include "BasePlayer.h"

//Default constructs a player object set to either AI or user player type
BasePlayer::BasePlayer(unsigned int playerType) : ai(playerType)
{	
	draws = 0;
	losses = 0;
	wins = 0;
	playerClassError = 0;
}

BasePlayer::~BasePlayer()
{
	//std::cout  << "Called BasePlayer DESTRUCTOR" << std::endl << std::endl;
}

//Resets the hands of the player so they can start again fresh   
void BasePlayer::playerReset()
{
	playerClassError = 0;
	return;
}