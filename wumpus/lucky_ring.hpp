#ifndef LUCKY_RING_HPP
#define LUCKY_RING_HPP

#include "event.hpp"


class lucky_ring : public event {
    private:
    public:

        /*
         * Funciton: lucky_ring
         * Description: The default constructor for the lucky ring class
         */
        lucky_ring() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the lucky ring event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters the room with the ring, they pick it up
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      true (bool): Returns true because the event is removed from the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter R
         */
        void print() const;

        /*
         * Funciton: ~lucky_ring
         * Description: The destuctor for the lucky ring class
         */
        ~lucky_ring() = default;

};


#endif