#include "gold.hpp"

// TODO Gold implementation (define gold member functions below)

void gold::percept() const{
    printw("You stub your toe on something heavy.\n");
}

bool gold::encounter(Player& p){
    // The player has the gold
    p.has_gold = true;
    return true;
}

void gold::print()const{
    // prints out the letter G to symbolize the gold
    printw("G");
}