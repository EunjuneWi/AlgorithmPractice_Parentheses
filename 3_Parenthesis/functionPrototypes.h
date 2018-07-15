/*
* FILE			: functionPrototypes.h
* PROJECT		: Maximizing the Value of an Arithmetic Expression
* PROGRAMMER	: Eunjune Wi
* FIRST VERSION	: 2018-07-15
* DESCRIPTION
*	This file contains prototypes of functions used in the project.
*/
#pragma once
#include <string>



using std::string;



// Functions in "parenthesis.cpp"
long long	getMaximumValue	(const string &exp);
long long	calculateExp	(long long a,			long long b,	char op);
void		getNumAndOp		(const string& exp,		
							 int** digits,			char** ops, 
							 int numberOfDigits,	int numberOfOps);

// Functions in "matrix.cpp"
void		createMatrix	(long long*** pMatrix,	int column,		int row);
void		freeMatrix		(long long*** pMatrix,	int rowSize);
void		fillMatrix		(long long*** pMinMatrix,	long long*** pMaxMatrix,
							 int* digits,			char* ops,		
							 int numberOfDigits,	int numberOfOps);
void		fillCell		(long long*** pMinMatrix,	long long*** pMaxMatrix, 
							 int* digits,			char* ops, 
							 int rowIndex,			int columnIndex);