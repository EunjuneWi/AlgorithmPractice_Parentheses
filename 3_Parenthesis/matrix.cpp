/*
* FILE			: matrix.cpp
* PROJECT		: Maximizing the Value of an Arithmetic Expression
* PROGRAMMER	: Eunjune Wi
* FIRST VERSION	: 2018-07-15
* DESCRIPTION
*	Functions in this file is used to handle matrix.
*	Two matrices are used to calculate maximum value of the expression
*	in this program.
*/



#include <vector>
#include <malloc.h>
#include "Constants.h"
#include "functionPrototypes.h"



using std::vector;



/*
* FUNCTION		: fillMatrix
* DESCRIPTION	: This function fills in two matrices 
*					which is used to find maximum value of the expression.
* PARAMETERS
*	long long***	pMinMatrix	: Pointer to the matrix which stores minimum value
*	long long***	pMaxMatrix	: Pointer to the matrix which stores maximum value
*	int*			digits		: Digits in the expression
*	char*			ops			: Operations in the expressions
*	int				numberOfDigits	: Number of digits in the expression
*	int				numberOfOps		: Number of operations in the expression
* RETURNS		: void
*/
void fillMatrix(long long*** pMinMatrix, long long*** pMaxMatrix,
				int* digits, char* ops, int numberOfDigits, int numberOfOps)
{
	// Fill in the matrix in order. Below is the example when there are 5 digits.
	// 0 tier: (0,0) (1,1) (2,2) (3,3) (4,4) 
	// 1 tier: (0,1) (1,2) (2,3) (3,4)
	// 2 tier: (0,2) (1,3) (2,4)
	// 3 tier: (0,3) (1,4)
	// 4 tier: (0,4) ==> Result
	
	int rowIndex = 0;
	int columnIndex = 0;
	int rowSize = numberOfDigits;
	int columnSize = numberOfDigits;

	// Iterate each cell
	int tierLevel = 0;
	for (tierLevel = 0; tierLevel < numberOfDigits; ++tierLevel)
	{
		for (rowIndex = 0; rowIndex < (rowSize - tierLevel); ++rowIndex)
		{
			columnIndex = rowIndex + tierLevel;

			// Fill in (x,y) which is [x == y]
			//		These are digits wihtout operation
			if (rowIndex == columnIndex)
			{
				(*pMinMatrix)[rowIndex][columnIndex] = digits[rowIndex];
				(*pMaxMatrix)[rowIndex][columnIndex] = digits[rowIndex];
			}
			// Otherwise calculate minimum and maximum value
			else
			{
				fillCell(pMinMatrix, pMaxMatrix, digits, ops, rowIndex, columnIndex);
			}
		}
	}
}



/*
* FUNCTION		: fillCell
* DESCRIPTION	: This function fills in selected cells in two matrices.
*				  Each cell is minimum value or maximum value of the available digits.
*				  The cell(x,y) is combination of other cells (x, 0 + j) and (1 + j, y)
*				  where [x =< j < y].
*				  Refer to the comment in the end of this function for detail
* PARAMETERS
*	long long***	pMinMatrix	: Pointer to the matrix which stores minimum value
*	long long***	pMaxMatrix	: Pointer to the matrix which stores maximum value
*	int*			digits		: Digits in the expression
*	char*			ops			: Operations in the expressions
*	int				rowIndex	: Index for location of the cell
*	int				columnIndex	: Index for location of the cell
* RETURNS		: void
*/
void fillCell(long long*** pMinMatrix, long long*** pMaxMatrix, 
			  int* digits, char* ops, int rowIndex, int columnIndex)
{
	// Flag used to find whether value has been calculated before
	bool trueForNevercalculated = true;		

	long long* pMinCell = &(*pMinMatrix)[rowIndex][columnIndex];
	long long* pMaxCell = &(*pMaxMatrix)[rowIndex][columnIndex];

	
	// Iterate all the possible combination for each cell
	int combIndex = 0;	// Index used to find combination for calculating cell in matrix
	for (combIndex = rowIndex; combIndex < columnIndex; ++combIndex)
	{
		// Array to store possible left operand and right operand
		long long leftSide[MIN_AND_MAX] = { 0 };
		long long rightSide[MIN_AND_MAX] = { 0 };

		leftSide[MIN_VALUE] = (*pMinMatrix)[rowIndex][combIndex];
		leftSide[MAX_VALUE] = (*pMaxMatrix)[rowIndex][combIndex];
		rightSide[MIN_VALUE] = (*pMinMatrix)[combIndex + 1][columnIndex];
		rightSide[MAX_VALUE] = (*pMaxMatrix)[combIndex + 1][columnIndex];

		char operation = ops[combIndex];

		// Check all the possible minimum value or maximum value for each cell
		int leftIndex = 0;
		int rightIndex = 0;
		for (leftIndex = 0; leftIndex < MIN_AND_MAX; ++leftIndex)
		{
			for (rightIndex = 0; rightIndex < MIN_AND_MAX; ++rightIndex)
			{
				long long temp = calculateExp(leftSide[leftIndex], rightSide[rightIndex], operation);

				if (trueForNevercalculated)
				{
					*pMinCell = temp;
					*pMaxCell = temp;
					trueForNevercalculated = false;
				}
				else
				{
					if (temp < *pMinCell)
					{
						*pMinCell = temp;
					}

					if (temp > *pMaxCell)
					{
						*pMaxCell = temp;
					}
				}
			}
		}
	}
}
// For math expression a + b - c
// (1,3) cell contains value calculated using b and c.
// This cell can be calculated by combining cells as below
//		(1,1) + (2,3)
//		(1,2) + (3,3)



/*
* FUNCTION		: freeMatrix
* DESCRIPTION	: This function frees memory allocated to matrix.
* PARAMETERS
*	long long***	pMatrix	: Pointer to the matrix to free
*	int				rowSize	: Number of rows in matrix
* RETURNS		: void
*/
void freeMatrix(long long*** pMatrix, int rowSize)
{
	// Iterate each row from the end to free
	int rowIndex = rowSize - 1;
	for (rowIndex = rowSize - 1; rowIndex >= 0; --rowIndex)
	{
		free((*pMatrix)[rowIndex]);
	}
	
	// Free pointer to each row
	free(*pMatrix);
}



/*
* FUNCTION		: createMatrix
* DESCRIPTION	: This function creates a matrix which is used for calculation.
* PARAMETERS
*	long long***	pMatrix	: Pointer to create the matrix 
*	int				column	: Column of the matrix
*	int				row		: Row of the matrix
* RETURNS		: void
*/
void createMatrix(long long*** pMatrix, int column, int row)
{
	int statusFlag = NO_ERROR;

	// Create Row, which is array of long long*
	*pMatrix = (long long**)malloc(sizeof(long long*) * row);
	if (*pMatrix == NULL)
	{
		statusFlag = MALLOC_FAIL;
	}

	// Create Columns for each row
	if (statusFlag == NO_ERROR)
	{
		int lengthIndex = 0;
		for (lengthIndex = 0; lengthIndex < row; ++lengthIndex)
		{
			(*pMatrix)[lengthIndex] = (long long*)malloc(sizeof(long long) * column);
			if (*pMatrix == NULL)
			{
				statusFlag = MALLOC_FAIL;
			}
		}
	}
}