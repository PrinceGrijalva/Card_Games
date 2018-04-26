//Many thanks to a thread in cpluscplus.com for the help in validating user input
//http://www.cplusplus.com/forum/articles/6046/

#include "ValidInput.h"

namespace VALIDINPUT 
{
	//Empty default constructor
	ValidInput::ValidInput()
	{

	}

	//Validate int input but uses unsigned int parameters 
	bool ValidInput::validIntInput(unsigned int & userNum)
	{
		std::string userNumber = "";

		//USER_INPUT_HERE-------------------------

		//Validate the user input; code same as in LetsPlay
		//Accepts values as long as they begin with integers or negative integers followed by anything else
		//Example: 2a, 2    a, 2+a: this all equals 2
		//Does not accept a2
		std::getline(std::cin, userNumber);

		std::stringstream myStream(userNumber);
		if (myStream >> userNum)
		{
			//std::cout << "userInput: " << userInput << std::endl;
			return true;
		}
		else
		{
			std::cout << "This is not an acceptable value." << std::endl;
			return false;
		}
	}

	//Validate int input and checks input length, but uses unsigned int parameter
	bool ValidInput::validIntInput(unsigned int & userNum,  int inputSize)
	{
		std::string userNumber = "";

		//USER_INPUT_HERE-------------------------

		//Validate the user input; code same as in LetsPlay
		//Accepts values as long as they begin with integers or negative integers followed by anything else
		//Example: 2a, 2    a, 2+a: this all equals 2
		//Does not accept a2
		std::getline(std::cin, userNumber);

		std::stringstream myStream(userNumber);
		if (myStream >> userNum && int(userNumber.size()) <= inputSize)
		{
			//std::cout << "userInput: " << userInput << std::endl;
			return true;
		}
		else
		{
			std::cout << "This is not an acceptable value or input is too long." << std::endl << std::endl;
			return false;
		}

	}

	//Typically programs ask a for a yes or no response from a user and this function should validate that call
	bool ValidInput::validStrYesNo()
	{
		std::string userInput = "";
		//Loop should continue until a satisfactory answer of yes or no is given.
		while (true)
		{
			std::getline(std::cin, userInput);

			//Answer should only be of length at most 3 chars for "yes" response.
			if (3 >= userInput.length())
			{
				if ("Y" == userInput || "y" == userInput || "Yes" == userInput
					|| "YES" == userInput || "yes" == userInput)
				{
					return true;
				}
				else if ("N" == userInput || "n" == userInput || "No" == userInput
					|| "NO" == userInput || "no" == userInput)
				{
					return false;
				}
				else
				{
					std::cout << "This is not Y/N. Try again: " << std::endl;
				}
			}
			else
			{
				std::cout << "This too long of an input. Try again: " << std::endl;
			}
		}
	}
}