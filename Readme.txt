/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/



All parts of the assignment were completed.
No bugs were encountered. 

To run the program, select the appropriate directory in the linux console. Once the directory is selected, use the "make all" command to compile the program.
Once the program is compiled, it can be run by typing "./" followed by the program's name, which in this case is "main".

This will run the main program. 

Please note that MaxBackStep is set at 1,000,000. This is because one of the 4 input files provided takes over 2 million back steps to solve. 
The MaxBackStep variable in main.cpp can be changed to your liking, by changing the number in line 16.

This program takes an input file. The input file should consist of 81 integers between 0 and 9 seperated by either a space or tab or end of line. 0 should correspond to an empty square
in the Sudoku Grid. If you want to change the input file, you can either rename the file you would like to run it on to "puzzle.txt", or change the filename in line 14 to the appropriate 
name and directory. If you change the code please recompile the code before running it. 

I have included 5 test files which can be used to test the program. Puzzle1 has no solutions. Puzzles 2-5 all have solutions. Puzzle 4 takes approximately 2,016,000 steps and therefore
will require the user to input "y" twice if the MaxBackStep is left unchanged. 

