#include "bottomless_pit.hpp"

// TODO Bottomless Pit implementation (define bottomless_pit member functions
// below)

void bottomless_pit::percept() const{
    printw("You feel a breeze.\n");
}

bool bottomless_pit::encounter(Player& p){
    // Creates a random number between 1 and 100
    int n = rand() % 101;
   
    // If the player has lucky ring uses left
    if (p.lucky_ring > 0){

        // If they do they don't fall into the pit
        p.fell_in_pit = false;

        // Decreases amount of lucky ring uses the user has
        p.lucky_ring -= 1;

    // If it's greater than 50 then the player falls in the pit
    } else if (n > 50){

        // The user fell in the pit
        p.fell_in_pit = true;
    }    
    return false;
}

void bottomless_pit::print()const{
    // prints out the letter P to symbolize a bottomless pit
    printw("P");
}

