#ifndef GOLD_HPP
#define GOLD_HPP

#include "event.hpp"

// TODO Gold interface (define the gold class and declare its member functions
// below)

class gold : public event {
    private:
    public:

        /*
         * Funciton: gold
         * Description: The default constructor for the gold class
         */
        gold() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the gold event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters the room with the gold, they pick it up
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      true (bool): Returns true because the event is removed from the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter G
         */
        void print() const;

        /*
         * Funciton: ~gold
         * Description: The destuctor for the gold class
         */
        ~gold() = default;

};

#endif
