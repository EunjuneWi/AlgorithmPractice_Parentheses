/*
* FILE			: parenthesis.cpp
* PROJECT		: Maximizing the Value of an Arithmetic Expression
* PROGRAMMER	: Eunjune Wi
* FIRST VERSION	: 2018-07-15
* DESCRIPTION
*	Functions in this file includes business rule of the program.
*	Some functions are the ones which support business rule.
*/



#include <cassert>
#include "Constants.h"
#include "functionPrototypes.h"



/*
* FUNCTION		: getMaximumValue
* DESCRIPTION	: This function adds parenthesis to the math expression
*					in order to find maximum value.
* PARAMETERS
*	const string&	exp		: Math expression in C++ string
* RETURNS
*	long long				: Maximum number from the expression
*/
long long getMaximumValue(const string& exp) {

	// Analyze which numbers and operations are in the math expression
	int* digits = NULL;
	char* ops = NULL;

	int numberOfDigits = (exp.size() / 2) + 1;
	int numberOfOps = exp.size() - numberOfDigits;

	getNumAndOp(exp, &digits, &ops, numberOfDigits, numberOfOps);

	// Make the matrix to store 
	long long** minMatrix = NULL;
	long long** maxMatrix = NULL;
	createMatrix(&minMatrix, numberOfDigits, numberOfDigits);
	createMatrix(&maxMatrix, numberOfDigits, numberOfDigits);

	// Fill in Matrix
	fillMatrix(&minMatrix, &maxMatrix, digits, ops, numberOfDigits, numberOfOps);

	// Get the result from matrix
	long long result = maxMatrix[0][numberOfDigits - 1];

	// Free all malloc
	free(digits);
	free(ops);
	freeMatrix(&minMatrix, numberOfDigits);
	freeMatrix(&maxMatrix, numberOfDigits);

	return result;
}



/*
* FUNCTION		: getNumAndOp
* DESCRIPTION	: This function extracts digits and operation from the expression
* PARAMETERS
*	const string&	exp		: Math expression in C++ string
*	int**			digits	: Pointer to store array of digits
*	char**			ops		: Pointer to store array of operations
*	int				numberOfDigits	: Number of digits in the expression.
*	int				numberOfOps		: Number of operations in the expression
* RETURNS		: void
*/
void getNumAndOp(const string& exp, int** digits, char** ops, int numberOfDigits, int numberOfOps)
{
	int statusFlag = NO_ERROR;

	// Allocate memory for each array
	*digits = (int*)malloc(sizeof(int) * numberOfDigits);
	if (*digits == NULL)
	{
		statusFlag = MALLOC_FAIL;
	}

	if (statusFlag == NO_ERROR)
	{
		*ops = (char*)malloc(sizeof(char) * numberOfOps);
		if (*ops == NULL)
		{
			statusFlag = MALLOC_FAIL;
		}
	}

	// Iterate expression and sort components in corresponding array
	if (statusFlag == NO_ERROR)
	{
		int digitIndex = 0;		// Index used for each array
		int opIndex = 0;

		int i = 0;
		for (i = 0; i < (int)exp.size(); ++i)
		{
			if (i % 2 == 0)
			{
				(*digits)[digitIndex] = exp.at(i) - '0';	// convert ascii value to int
				++digitIndex;
			}
			else
			{
				char temp = exp.at(i);
				if (temp == '+')
				{
					(*ops)[opIndex] = PLUS;
				}
				else if (temp == '-')
				{
					(*ops)[opIndex] = MINUS;
				}
				else if (temp == '*')
				{
					(*ops)[opIndex] = MULTI;
				}

				++opIndex;
			}
		}
	}
}



/*
* FUNCTION		: calculateExp
* DESCRIPTION	: This function calculates math expression with two operands.
* PARAMETERS
*	long long	a	: Left operand
*	long long	b	: Right operand
*	char		op	: Opearations
* RETURNS		
*	long long		: Result of the calculation
*/
long long calculateExp(long long a, long long b, char op) 
{
	long long result = 0;

	if (op == MULTI) {
		result = a * b;
	}
	else if (op == PLUS) {
		result = a + b;
	}
	else if (op == MINUS) {
		result = a - b;
	}

	return result;
}