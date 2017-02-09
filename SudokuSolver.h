#ifndef _SUDOKU_SOLVER
#define _SUDOKU_SOLVER

#include "SolverInterface.h"
#include "SudokuBoard.h"
#include "LinkedStack.h"
#include <string>

using namespace std;

class SudokuSolver : public SolverInterface<int>
{
	private:
	SudokuBoard<int> _board_; //The puzzle is stored in a SudokuBoard<int> data type.
	LinkedStack<int> _possibilities_[82]; //The linked stacks store the possible values for all empty and modifiable cells.
	int _currentPlace_; //The location of the current square that is being worked on.
	
	 /** Updates the specified square with the value in number.
	 @post  The square in _board_ indexed at (row,col) now stores the value in number.
	 @param number  The value to be inserted into the board.
	 @param row  The first index of the board space which is being requested.
	 @param col  The second index of the board space which is being requested.
	 @return  True if number was successfully inserted, false otherwise. */
	 
	bool insert(const int& number, const int& row, const int& col);
	
	 /** Updates the specified square with the default empty value of 0.
	 @post  The square in _board_ indexed at (row,col) now stores the value 0.
	 @param row  The first index of the board space which is being requested.
	 @param col  The second index of the board space which is being requested.
	 @return  True if number was successfully removed, false otherwise. */
	bool remove(const int& row, const int& col);
	
	 /** Sets _currentPlace_ to the location of the first encountered square with possibilities.
	 @post  The square referenced by _currentPlace_ is the latest which has available possibilities. _currentPlace_ is 0 if nothing is found.
	 @return  True if a square with possibilities was found, false otherwise. */
	bool goBack(); 
	
	 /** Provides the index of the next square that has a value of 0.
	 @return  The index of the next empty square, or 0 if no such square is found.*/
	int nextEmpty() const;
	
	 /** Updates the _possibilities_ stack of the _currentPlace_ with all valid possibilities for that square.
	 @post  The _possibilies_stack at _currentPlace_ contains all possible values. If there are no valid values then it will be empty.*/
	void createPossibilities();
	
	 /** Returns an integer containing all missing values from the Box in numerical order.
	 @param row  The first index of the board space which is being requested.
	 @param col  The second index of the board space which is being requested.
	 @return  An integer representing all missing values in the box. 0 is returned if nothing is missing.*/
	int getMissingInBox(const int& row, const int& col) const;
	
	 /** Returns an integer containing all missing values from the row in numerical order.
	 @param row  The first index of the board space which is being requested.
	 @param col  The second index of the board space which is being requested.
	 @return  An integer representing all missing values in the row. 0 is returned if nothing is missing.*/
	int getMissingInRow(const int& row, const int& col) const;
	
	 /** Returns an integer containing all missing values from the Col in numerical order.
	 @param row  The first index of the board space which is being requested.
	 @param col  The second index of the board space which is being requested.
	 @return  An integer representing all missing values in the col. 0 is returned if nothing is missing.*/
	int getMissingInCol(const int& row, const int& col) const;
	
	 /** Parses through the specified input file and updates all board values with the ones specified in the file.
	 @post  The board has the values specified in the file in each corresponding square. 
	 @param filename  The string which represents the filename and possibly path to the file which should be read.
	 @return  Returns true if the file was successfully read. Returns false if there was some error and no change was made to the board.*/
	bool readInputFile(string filename);
	
	 /** Tests whether the current state of the board has any contradictions.
	 @return  Returns true if there are contradictions and fale if there aren't.*/
	bool hasContradictions() const;
	
	public:
	SudokuSolver(); // Default constructor.
	SudokuSolver(string filename); // Custom constructor with a specified filename which initializes the values of the board to those in the file.
	
	bool SolvePuzzle(const int& maxBackSteps);
	void DisplayPuzzle() const;
};// end SudokuSolver

#include "SudokuSolver.cpp"
#endif
