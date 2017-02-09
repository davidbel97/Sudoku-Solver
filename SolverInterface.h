/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
/** @file SolverInterface.h */

#ifndef _SOLVER_INTERFACE
#define _SOLVER_INTERFACE

template <class ItemType>
class SolverInterface
{
	public:
	/** Solves the puzzle.
	@param maxBackSteps  the maximum number of times that it may backtrack while solving the puzzle.
    @return True if the puzzle was solved, or false if not or it reached the maximum number of steps. */
	virtual bool SolvePuzzle(const int& maxBackSteps) = 0;
	
	/** Displays the current state of the puzzle in the console output.
    @post The console output should have a displayed representation of the puzzle.*/
	virtual void DisplayPuzzle() const = 0;
};// end SolverInterface
#endif