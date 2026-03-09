#ifndef ARROW_HPP
#define ARROW_HPP

#include "event.hpp"

// TODO Arrow interface (define the arrow class and declare its member functions
// below)

class arrow : public event {
    private:
    public:

        /*
         * Funciton: arrow
         * Description: The default constructor for the arrow class
         */
        arrow() = default;


        /*
         * Funciton: encounter
         * Description: If the player enters a room with an arrow they pick it up
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      true (bool): returns true because the event needs to be removed from the
         *                   gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter A
         */
        void print() const;


        /*
         * Funciton: ~arrow
         * Description: The destuctor for the arrow class
         */
        ~arrow() = default;

};

#endif
