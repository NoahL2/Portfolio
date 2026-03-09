#ifndef BAT_SWARM_HPP
#define BAT_SWARM_HPP

#include "event.hpp"

// TODO Bat Swarm interface (define the bat_swarm class and declare its member
// functions below)
class bat_swarm : public event {
    private:
    public:

        /*
         * Funciton: bat_swarm
         * Description: The default constructor for the bat_swarm class
         */
        bat_swarm() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the bat event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters a room with a bat swarm they get confused
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      false (bool): Returns false because the event stays on the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter B
         */
        void print() const;

        /*
         * Funciton: ~bat_swarm
         * Description: The destuctor for the bat_swarm class
         */
        ~bat_swarm() = default;

};

#endif
