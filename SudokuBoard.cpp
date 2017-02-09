/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
#include "SudokuBoard.h"

template<class ItemType>
SudokuBoard<ItemType>::SudokuBoard()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			_board_[i][j] = 0; // all values default to 0
		}// end for
	}//end for
}//end of SudokuBoard()

template<class ItemType>
SudokuBoard<ItemType>::SudokuBoard(const ItemType startingValues[10][10])
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			_board_[i][j] = startingValues[i][j]; // all values set to corresponding ones in startingValues
		}//end for
	}//end for
}// end of SudokuBoard(startingValues)

template<class ItemType>
ItemType SudokuBoard<ItemType>::Get(const int& row, const int& col) const
{
	if((row < 0 || row > 9) || (col < 0 || col > 9))
	{ // if some inappropriate location is being requested then a default value of 0 is returned.
		ItemType endVal = 0;
		return endVal;
	}// end if
	else
		return _board_[row][col];
}// end of Get()

template<class ItemType>
bool SudokuBoard<ItemType>::Set(const ItemType& newValue, const int& row, const int& col)
{
	if((row < 0 || row > 9) || (col < 0 || col > 9))
	{// if some inappropriate location is being requested then false is returned and no change is made.
		return false;
	}//end if
	else
	{// Otherwise the value is set to the newValue and true is returned.
		_board_[row][col] = newValue;
		return true;
	}//end else
}// end of Set()