#ifndef ValidInput_H
#define ValidInput_H

#include <iostream>
#include <sstream>

/*
* This class serves as a way to validate any user input, in the following ways:
*	Use to limit length of input on strings
*	Use to check if input is an int (doesn't work on unsigned though)
*	Use to check if input is an int and limits length of input
*	Returns a bool to show if input was acceptable or not
* This should have unlimited uses in any program that takes inputs and needs them validated.
*/

namespace VALIDINPUT
{
	class ValidInput {
	public:
		ValidInput();
		bool validIntInput(unsigned int & userNum);
		bool validIntInput(unsigned int & userNum, int inputSize = 20);
		bool validStrYesNo();
	};
}

#endif // !ValidInput_H