/*! \file main.cc */
// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

#include "game.h"
#include "othello.h"
using namespace main_savitch_14;


int main()
{
	Othello theGame;
	theGame.restart();
	/*!	\fn restart()
		\brief Sets the newly created Othello game board to the starting position.
	*/

	theGame.play();
}
