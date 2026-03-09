#include "lucky_ring.hpp"

void lucky_ring::percept() const{
    printw("You feel like luck is on your side, today.\n");
}

bool lucky_ring::encounter(Player& p){
    
    // If the player collects the lucky ring two uses are added to the counter
    p.lucky_ring += 2;
   
    return true;
}

void lucky_ring::print()const{
    // prints out the letter R to symbolize the lucky ring
    printw("R");
}