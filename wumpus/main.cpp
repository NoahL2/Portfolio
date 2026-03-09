/*
 * Author: Noah Letter
 * Description: This program simulates a game where you search for gold and avoid 
 * 				obstacles. The player is first asked to enter the size of the gameboard,
 * 				then they are asked if they want to play in debug mode or not. If they
 * 				select yes then symbols for all the events will be printed on the 
 * 				gameboard. If they select no then nothing is printed out. There are 2
 * 				obstacles that can kill the player, the wumpus which kills the player
 * 				immediately, and the bottomless pit which has a 50% chance of the player 
 * 				falling in. There's are bat swarms that will confuse the player, this
 * 				means that the players next move after entering the swarm is random. If
 * 				the player finds the pile of gold and makes it back to the escape rope
 * 				which is at the same spot as the player started they win. There are two
 * 				arrows in random rooms and if the player picks one up they can shoot it
 * 				at the wumpus from up to 3 rooms away. If the arrow hits then the wumpus
 * 				dies and the player wins. If the arrow misses then the wumpus wakes up
 * 				and starts moving around. There is a lucky ring in one random room. If
 * 				the player finds it they don't die from the pits or wumpus. It only has
 * 				two uses though. Each event has a percept that prints out when the player
 * 				is adjcent to the room the event is in. The player moves using w, a, s,
 * 				or d, and fires the arrow by pressing f then the direction they want it
 * 				to go.  
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"

using std::cout;
using std::cin;
using std::endl;

/*
 * Function: get_width
 * Description: Prompts the user for the game board width (# of columns)
 * Returns (int): Valid width supplied by user
 */
int get_width() {
	int width;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid width!" << endl <<
				endl;
		}
		first = false;
		cout << "Enter the game board width between 4 and 30: ";
		cin >> width;
	} while(width < 4 || width > 30);
	return width;
}

/*
 * Function: get_height
 * Description: Prompts the user for the game board height (# of columns)
 * Returns (int): Valid height supplied by user
 */
int get_height() {
	int height;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid height!" << endl <<
				endl;
		}
		first = false;
		cout << "Enter the game board height between 4 and 30: ";
		cin >> height;
	} while(height < 4 || height > 30);
	return height;
}

/*
 * Function: get_debug
 * Description: Prompts the user whether they want to play in debug mode
 * Returns (bool): True if the user wants to play in debug mode. False
 * 		otherwise.
 */
bool get_debug() {
	int debug_input;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid input!" << endl <<
				endl;
		}
		first = false;
		cout << "Would you like to play in debug mode? (1-yes, 0-no): ";
		cin >> debug_input;
	} while(debug_input != 0 && debug_input != 1);
	return debug_input == 1;
}

int main()
{
	// Set the random seed
	srand(time(nullptr));


	// Ask user for width and height of game board
	int width = get_width();
	int height = get_height();

	// Ask user whether they want debug mode
	bool debug = get_debug();

	// ncurses functions
	cbreak();
	initscr();


	// Construct game object
	game g(width, height, debug);

	//Play game
	g.play_game();

	// End of the ncurses functions
	raw();
	endwin();

	return 0;
}
