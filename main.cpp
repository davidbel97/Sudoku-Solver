/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
#include "SudokuSolver.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	SudokuSolver test1 = SudokuSolver("puzzle.txt"); 
	string answer; // used to store the user's answer if input is needed.
	int maxBackSteps = 1000000; // This number may be modified to change the maxBackSteps. 1 million is used here because puzzle 4 requires over 2 million steps.
	bool solved = test1.SolvePuzzle(maxBackSteps); // the first attempt is performed seperately.
	while(!solved)
	{// as long as the puzzle is not solved it will prompt the user with the following.
		while(true)
		{ // this while loop is in place for error checking of the user's input.
			cout << "Would you like it to try another " << maxBackSteps << " steps(max)? (y, or n): ";
			cin >> answer;
			if(answer == "y" || answer == "n")
				break;
		}// end while
		if(answer == "n")
			break;
		else
		{
			solved = test1.SolvePuzzle(maxBackSteps);
		}// end else
	}// end while
	if(solved)
	{
		cout << "The puzzle has been successfully solved. Here is the solved puzzle:" << endl << endl;
		test1.DisplayPuzzle();
	} // end if
	else
	{
		cout << "Here is the current state of the unsolved puzzle." << endl << endl;
		test1.DisplayPuzzle();
	} // end else
	return 1;
}