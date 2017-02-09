/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
#include "SudokuSolver.h"
#include <string>
#include <fstream>
#include <iostream>
#include "LinkedStack.h"

using namespace std;

SudokuSolver::SudokuSolver() : _currentPlace_(0)
{
}//end SudokuSolver()

SudokuSolver::SudokuSolver(string filename)
{
	bool test = readInputFile(filename);
	if(!test)
		std::cout << "File is invalid and could not be read. Default initialization used instead." << endl;
	_currentPlace_ = 0;
}//end SudokuSolver(filename)

bool SudokuSolver::SolvePuzzle(const int& maxBackSteps)
{
	bool failSafe;
	if(_currentPlace_ == 0)
	{ //If the puzzle is currently in either an initial position, then this block needs to be run.
		if(hasContradictions())
		{// Testing for contradictions only needs to occur in the initial position as no following moves can result in a contradiction.
			std::cout << "This Sudoku puzzle has contradictions." << endl;
			return false; //If a contradiction exists then the puzzle cannot be solved. 
		} //end if.
		_currentPlace_ = nextEmpty(); // The current square is shifted to the first empty square.
		if(_currentPlace_ == 0)
		{ //if there is no empty square or the only empty one is 0, then the puzzle is already solved. 
			std::cout << "This Sudoku puzzle is already solved." << endl;
			return true;
		} //end if
		createPossibilities(); // The possibilities for the first empty square are made.
	}//end if
	int numSteps = 0; //Keeps track of the number of backsteps
	int value; //Used to hold the value stored in the board if it needs to be checked. 
	while(numSteps < maxBackSteps)
	{ // Loop to keep running until the max nuber of steps is reached or the puzzle is determined to be solved or unsolvable.
		if(_possibilities_[_currentPlace_].isEmpty())
		{ //If at any point the current square has no possibilities at the start of a turn, then the solver must go back.
			failSafe = goBack();
			if(!failSafe)
			{ // If failsafe is false then there all backsteps have been made and no possible solution exists.
				std::cout << "This Sudoku puzzle has no solution." << endl;
				return false;
			} //end if
			failSafe = remove(((_currentPlace_-1)/9)+1, ((_currentPlace_-1)%9)+1); //after a backstep is made, that square must be emptied.
			if(!failSafe)
			{ // If for some reason the square cannot be removed then an error has occurred and the solver terminates.
				std::cout << "There was an error in removing square " << _currentPlace_ << "." << endl;
				return false;
			} // end if
			_possibilities_[_currentPlace_].pop(); //the top of the possibilities is popped as that is the possibility which was just tried. 
			numSteps++; // a backstep has just occurred so numSteps is incremented.
		} // end if
		else
		{ // If the current square has possibilities then the top possibility must be tried and the next square must be prepared.
			value = _possibilities_[_currentPlace_].peek(); //peek is used so that if/when a backstep is made, this possibility can still be removed.
			failSafe = insert(value, ((_currentPlace_-1)/9)+1, ((_currentPlace_-1)%9)+1);
			if(!failSafe)
			{ // if for some reason the value cannot be inserted then an error has occurred and the solver terminates.
				std::cout << "There was an error while inserting " << value << " into square " << _currentPlace_ << "." << endl;
				return false;
			}//end if
			_currentPlace_ = nextEmpty(); //After inserting the possibility for the current space the solver moves on to the next one.
			if(_currentPlace_ == 0) //if there is no next space then the solver has successfully solved the puzzle and true is returned. 
				return true;
			else //Otherwise the possibilities for the next square are generated. 
				createPossibilities();
		}//end else
	}//end while
	std::cout << "This Sudoku puzzle could not be solved in " << maxBackSteps << " steps." << endl;
	return false;
}//end SolvePuzzle

void SudokuSolver::DisplayPuzzle() const
{
	for(int i = 1; i < 10; i++)
	{
		for(int j = 1; j < 10; j++)
		{
			std::cout << _board_.Get(i, j) << " ";
			if(j == 9)
				std::cout << endl;
		}// end for
	}// end for
	return;
}//end DisplayPuzzle()

//end of all public functions

bool SudokuSolver::insert(const int& number, const int& row, const int& col)
{
	return _board_.Set(number, row, col); // False if the modification of the board is unsuccessful. True otherwise.
}// end insert()

bool SudokuSolver::remove(const int& row, const int& col)
{
	return _board_.Set(0, row, col); // False if modification of the board is unsuccessful. True otherwise.
}// end remove()

bool SudokuSolver::goBack()
{
	while(_currentPlace_ > 0)
	{
		_currentPlace_--;
		if(!(_possibilities_[_currentPlace_].isEmpty())) //True only if a modifiable square is found. Otherwise false is returned. (a modifiable square has a stack with items in it)
			return true;
	}// end while
	return false;
}// end goBack()

int SudokuSolver::nextEmpty() const
{
	for(int i = _currentPlace_ + 1; i <= 81; i++)
	{
		if(_board_.Get(((i-1)/9)+1, ((i-1)%9)+1) == 0)// if the current square has a value of 0 then it is the next empty one.
			return i;
	}// end for
	return 0;
}// end nextEmpty()

void SudokuSolver::createPossibilities()
{
	int box, row, col;
	box = getMissingInBox(((_currentPlace_-1)/9)+1, ((_currentPlace_-1)%9)+1); // the missing numbers from the box
	row = getMissingInRow(((_currentPlace_-1)/9)+1, ((_currentPlace_-1)%9)+1); // the missing numbers from the row
	col = getMissingInCol(((_currentPlace_-1)/9)+1, ((_currentPlace_-1)%9)+1); // the missing numbers from the col
	bool boxa[10] = {0}; // An array so that the missing numbers in the box can be indexed.
	bool rowa[10] = {0}; // An array so that the missing numbers in the row can be indexed.
	bool cola[10] = {0}; // An array so that the missing numbers in the col can be indexed.
	while(box > 0)
	{ // this while loop maps the missing numbers from box into boxa
		boxa[box%10] = true;
		box = box/10;
	}// end while
	while(row > 0)
	{ // this while loop maps the missing numbers from row into rowa
		rowa[row%10] = true;
		row = row/10;
	}// end while
	while(col > 0)
	{ // this while loop maps the missing numbers from col into cola
		cola[col%10] = true;
		col = col/10;
	}// end while
	for(int i = 1; i < 10; i++)
	{ // if the corresponding entries from boxa, rowa, and cola are all true, then that number is a valid possibility and is added to the possibilities stack for that space.
		if(boxa[i] && rowa[i] && cola[i])
			_possibilities_[_currentPlace_].push(i);
	}// end for
	return;
}// end createPossibilities()

int SudokuSolver::getMissingInBox(const int& row, const int& col) const // assert that row and col are > 0 and < 10 
{ 
	int set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // keeps track of what values have been seen.
	int rowHolder, colHolder, value;
	rowHolder = row - 1;
	rowHolder -= rowHolder % 3; // places the upper row of the box in rowholder
	colHolder = col - 1;
	colHolder -= colHolder % 3; // places the left col of the box in colholder
	for(int i = rowHolder; i <= rowHolder + 2; i++)
	{
		for(int j = colHolder; j <= colHolder + 2; j++)
		{ // these for loops check each square in the box and save the numbers which have already been seen.
			value = _board_.Get(i + 1, j + 1);
			if(value != 0)
				set[value - 1] = 0;
		}// end for
	}// end for
	value = 0;
	for(int i = 0; i < 9; i++)
	{
		if(set[i] != 0)
		{ // checks each digit and if it is still a nonzero value then it is added to the compiled number for missingInBox.
			value *= 10;
			value += set[i];
		} // end if
	}// end for
	return value;
} // end getMissingInBox()

int SudokuSolver::getMissingInRow(const int& row, const int& col) const // assert that row and col are > 0 and < 10
{
	int set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // keeps track of what values have been seen.
	int value;
	for(int i = 1; i < 10; i++)
	{ // goes through the 9 squares in the row and checks their values.
		value = _board_.Get(row, i);
		if(value != 0)
			set[value - 1] = 0;
	} // end for
	value = 0;
	for(int i = 0; i < 9; i++)
	{
		if(set[i] != 0)
		{ // checks each digit and if it is still a nonzero value then it is added to the compiled number for missingInBox.
			value *= 10;
			value += set[i];
		} // end if
	}// end for
	return value;
}// end getMissingInRow()

int SudokuSolver::getMissingInCol(const int& row, const int& col) const
{
	int set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // keeps track of what values have been seen.
	int value;
	for(int i = 1; i < 10; i++)
	{ // goes through the 9 squares in the col and checks their values.
		value = _board_.Get(i, col);
		if(value != 0)
			set[value - 1] = 0;
	}// end for
	value = 0;
	for(int i = 0; i < 9; i++)
	{
		if(set[i] != 0)
		{ // checks each digit and if it is still a nonzero value then it is added to the compiled number for missingInBox.
			value *= 10;
			value += set[i];
		} // end if
	}// end for
	return value;
}// end getMissingInBox()

bool SudokuSolver::readInputFile(string filename)
{
	int counter = -1; // keeps track of how many integers have been taken from the file. 
	int fileValues[10][10] = {0}; // stores the values which will be used to initialize the board.
	int value; // holds a value from the file.
	ifstream PuzzleFile;
	PuzzleFile.open(filename.c_str());
	while(PuzzleFile >> value)
	{ // parses through the entire file and holds the values in value.
		counter++; //counter increments with each iteration.
		if(value < 0 || value > 9) // if any of the values are not between 0 and 9 then this is not a valid SudokuFile and the function returns false.
			return false;
		if(counter > 80) // if there are more than 81 numbers in the file then this is not a valid SudokuFile and the function returns false. 
			return false;
		fileValues[(counter / 9) + 1][(counter%9)+1] = value; // the value is stored in the appropriate place in the array.
	} // end while
	if(counter < 80) // If there aren't enough numbers in the file then it is an invalid SudokuFile and the function returns false. 
		return false;
	for(int i = 1; i < 10; i++)
	{
		for(int j = 1; j < 10; j++)
		{
			_board_.Set(fileValues[i][j], i, j); // _board_ is filled with the values in fileValues
		}// end for
	} // end for
	return true;
} // end readInputFile()

bool SudokuSolver::hasContradictions() const
{
	int val; // used as a placeholder for values taken from the board.
	//rows
	for(int i = 1; i < 10; i++)
	{// iterates through the rows.
		int rowVal[10] = {0}; // A new rowVal array is initialized for each row.
		for(int j = 1; j < 10; j++)
		{ // iterates through the squares in the rows.
			val = _board_.Get(i, j);
			if(val != 0)
			{ //Adds the occurence of the number to the rowVal array, and checks that index of the array. If more than 1 has been found then true is returned. 
				rowVal[val]++;
				if(rowVal[val] > 1)
					return true;
			}// end if
		}// end for
	}// end for
	//columns
	for(int i = 1; i < 10; i++)
	{// iterates through the cols.
		int colVal[10] = {0}; // A new colVal array is initialized for each col.
		for(int j = 1; j < 10; j++)
		{ // iterates through the squares in the cols.
			val = _board_.Get(j, i);
			if(val != 0)
			{ //Adds the occurence of the number to the colVal array, and checks that index of the array. If more than 1 has been found then true is returned. 
				colVal[val]++;
				if(colVal[val] > 1)
					return true;
			}// end if
		}// end for
	}// end for
	//boxes
	for(int i = 1; i < 10; i+=3)
	{
		for(int j = 1; j < 10; j+=3)
		{ // this and the previous for loop iterates through the voard getting the upper left hand corner of each.
			int boxVal[10] = {0}; // A new boxVal array is initialized for each box.
			for(int k = i; k < i+3; k++)
			{
				for(int l = j; l < j+3; l++)
				{ // previous two for loops iterate through every square in the box
					val = _board_.Get(k, l);
					if(val != 0)
					{ // Adds the occurence of the number to the boxVal array, and checks that index of the array. If more than 1 has been found then true is returned. 
						boxVal[val]++;
						if(boxVal[val] > 1)
							return true;
					}// end if
				}// end for
			}// end for
		}// end for
	}// end for
	return false;
} // end of findContradictions()