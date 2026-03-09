#include "arrow.hpp"

// TODO Arrow implementation (define arrow member functions below)


bool arrow::encounter(Player& p){

    // Increases the the number of arrows the player has
    p.num_arrows +=1;
    
    return true;
}

void arrow::print()const{
    // Prints out A to symbolize arrow
    printw("A");
}

