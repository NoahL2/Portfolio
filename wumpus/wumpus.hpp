#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include "event.hpp"

// TODO Wumpus interface (define the wumpus class and declare its member
// functions below)

class wumpus : public event {
    private:
        int wumpus_row = 0;
        int wumpus_col = 0;
        // bool if_wumpus_dead = false;
    public:

        /*
         * Function: wumpus
         * Description: This is the default constructor for the wumpus class
         */
        wumpus() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the wumpus event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters the room with the wumpus, they get eaten
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      false (bool): Returns false because the event stays on the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter W
         */
        void print() const;

		/*
		 * Function: get_wumpus_row
		 * Description: Gets the row index of the wumpus
		 * Returns: 
		 * 		wumpus_row (int): The the row index of the wumpus
		 */
        int get_wumpus_row();

		/*
		 * Function: get_wumpus_col
		 * Description: Gets the column index of the wumpus
		 * Returns: 
		 * 		wumpus_row (int): The the column index of the wumpus
		 */
        int get_wumpus_col();

		/*
		 * Function: set_wumpus_row
		 * Description: Sets the row index of the wumpus to the random height that is
         *              generated when putting the wumpus event into the vector
		 * Parameters: 
		 * 		new_row (int): The random height generated when putting the wumpus event
         *                     into the vector
		 */
        void set_wumpus_row(int new_row);

		/*
		 * Function: set_wumpus_col 
		 * Description: Sets the column index of the wumpus to the random width that is
         *              generated when putting the wumpus event into the vector
		 * Parameters: 
		 * 		new_col (int): The random width generated when putting the wumpus event
         *                     into the vector
		 */
        void set_wumpus_col(int new_col);


        /*
         * Funciton: ~wumpus
         * Description: The destuctor for the wumpus class
         */
        ~wumpus() = default;

};

#endif
