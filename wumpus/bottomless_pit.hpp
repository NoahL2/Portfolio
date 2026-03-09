#ifndef BOTTOMLESS_PIT_HPP
#define BOTTOMLESS_PIT_HPP

#include "event.hpp"

// TODO Bottomless Pit interface (define the bottomless_pit class and declare
// its member functions below)

class bottomless_pit : public event {
    private:
    public:

        /*
         * Funciton: bottomless_pit
         * Description: The default constructor for the bottomless pit class
         */
        bottomless_pit() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the bottomless pit event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters a room with a bottomless pit they have a 50%
         *              chance of falling in
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      false (bool): Returns false because the event stays on the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter P
         */
        void print() const;

        /*
         * Funciton: ~bottomless_pit
         * Description: The destuctor for the bottomless_pit class
         */
        ~bottomless_pit() = default;

};


#endif
