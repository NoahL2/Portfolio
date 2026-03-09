#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"

// TODO Escape rope interface (define the escape_rope class and declare its
// member functions below)
class escape_rope : public event {
    private:
    public:

        /*
         * Funciton: escape_rope
         * Description: The default constructor for the escape rope class
         */
        escape_rope() = default;

        /*
         * Funciton: encounter
         * Description: If the player enters the room with the escape rope and they
         *              have the gold they can escape
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      false (bool): Returns false because the event stays on the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter E
         */
        void print() const;

        /*
         * Funciton: ~escape_rope
         * Description: The destuctor for the escape_rope class
         */
        ~escape_rope() = default;

};

#endif
