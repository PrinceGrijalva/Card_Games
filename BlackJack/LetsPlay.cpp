#include "LetsPlay.h"

namespace LETSPLAY
{
	//Default Constructor
	LetsPlay::LetsPlay()
	{
		//INITIALIZATION----------------------------
		std::string nameOfGame = "";
		unsigned int numberOfGame = 0;
		bool quit = false;
		VALIDINPUT::ValidInput validate;

		//INTRODUCTION-------------------------------
		std::cout << "Welcome to this collection of Card Games" <<
			std::endl << "Programmed by Prince Grijalva" << std::endl;


		//USER_INPUT----------------------------------
		//Validate the user input for game choice; code from website above
		//Accepts values as long as they begin with integers or negative integers followed by anything else
		//Example: 2a, 2    a, 2+a: this all equals 2
		//Does not accept a2
		try
		{
			while (!quit)
			{
				//Prints out gameList array 
				for (unsigned int i = 0; i <= gameList.size() - 1; i++)
				{
					std::cout << i << ". " << gameList[i] << std::endl;
				}
				std::cout << std::endl;
				std::cout << "Please enter the number of the game you want to play or 0 to quit: " << std::endl;
				if (validate.validIntInput(numberOfGame, 4))
				{
					//PROGRAM_START------------------------
					if (1 == numberOfGame)
					{	//Black Jack selected:
						BLACKJACK::BlackJack gameOn;
					}
					else if (2 == numberOfGame)
					{	//Poker selected:
						std::cout << "Poker to be available later." << std::endl;
					}
					else if (3 == numberOfGame)
					{	//War selected:
						std::cout << "War to be available later." << std::endl;
					}
					else if (0 == numberOfGame)
					{	//Quit selected:
						quit = true;
					}
					else
					{
						// Any unsigned int that isn't acceptable goes here and program loops.
						std::cout << "This is not an acceptable number. Try again." << std::endl << std::endl;
					}
				}
			}

			//PROGRAM_FINISHED---------------------------------
			//Standard exit message
			std::cout << std::endl << "Thank you for playing.";
			std::cout << std::endl << "Game Over" << std::endl;
		}
		catch (std::logic_error & e)
		{
			std::cout << e.what() << std::endl << "Sorry there was a logic error." << std::endl;
		}
		catch (std::runtime_error & e)
		{
			std::cout << std::endl << "Sorry there was a runtime error." << std::endl;
		}
		catch (...)
		{
			//Error exit message; Can contain nothing
			std::cout << std::endl << "Sorry there was an error." << std::endl;
		}
		std::cout << "Exiting....." << std::endl;
	}
}

