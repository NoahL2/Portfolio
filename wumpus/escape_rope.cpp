#include "escape_rope.hpp"

// TODO Escape rope implementation (define escape_rope member functions below)

bool escape_rope::encounter(Player& p){
    // If the player has the gold
    if (p.has_gold){

        // They can escape
        p.escaped = true;
    }
    
    return false;
}

void escape_rope::print()const{
    // Prints out the letter E to symbolize the escape rope
    printw("E");
}