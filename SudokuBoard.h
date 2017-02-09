/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
#ifndef _SUDOKU_BOARD
#define _SUDOKU_BOARD

#include "BoardInterface.h"

template<class ItemType>
class SudokuBoard : public BoardInterface<ItemType>
{
	private:
	ItemType _board_[10][10]; // The values in the board are stored in a 10x10 2-d array
	
	public:
	SudokuBoard(); //default constructor
	SudokuBoard(const ItemType startingValues[10][10]); //custom constructor. Sets all values of the board to corresponding ones in startingValues.
	
	ItemType Get(const int& row, const int& col) const;
	bool Set(const ItemType& NewValue, const int& row, const int& col);
}; //end SudokuBoard

#include "SudokuBoard.cpp"
#endif
