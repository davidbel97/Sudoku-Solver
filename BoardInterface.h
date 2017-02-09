/*
Author: David Belinsky
Class: CSCI 235 section 6
Instructor: Silvano Bernabel
Assignment: 3
*/
/** @file BoardInterface.h */

#ifndef _BOARD_INTERFACE
#define _BOARD_INTERFACE

template<class ItemType>
class BoardInterface
{
public:

   /** Returns the value stored in the specified location on the board.
    @param row  The first index of the board space which is being requested.
	@param col  The second index of the board space which is being requested.
    @return The item stored at location (row,col). The default value if the search cannot be performed is 0. */
   virtual ItemType Get(const int& row, const int& col) const = 0;
   
   /** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry replaces the value in the specified board space.
    @param newEntry The new value to be set in the board space.
	@param row  The first index of the board space which is being requested.
	@param col  The second index of the board space which is being requested.
    @return True if the addition is successful or false if not. */
   virtual bool Set(const ItemType& newEntry, const int& row, const int& col) = 0;
}; // end BoardInterface
#endif