/*
* FILE			: main.cpp
* PROJECT		: Maximizing the Value of an Arithmetic Expression
* PROGRAMMER	: Eunjune Wi
* FIRST VERSION	: 2018-07-15
* DESCRIPTION	
*	This program is to add parentheses to a given arithmetic expression
*	to maximize its value.
*	In order to find the maximum value, this program finds all the possible
*	minimum value and maximum value for each combination of the operands.
*	The expression only has +, -, * for operation.
* NOTES			
*	This problem is from 'Algorithmic Design and Techniques' class,
*	and its purpose is to practice dynamic programming.
*	The starter file from the course has main() and includes vector & C++ string.
*	Yet this program is written mostly in C to enhance C programming skill.
*/



#include <iostream>
#include "Constants.h"
#include "functionPrototypes.h"



int main() {
	// Enter math expression
	string exp;
	std::cin >> exp;

	// Find maximum value
	std::cout << getMaximumValue(exp) << std::endl;

	return 0;
}
