#include "wumpus.hpp"

// TODO Wumpus implementation (define wumpus member functions below)
void wumpus::percept() const{
    printw("The hairs stand up on the back of your neck.\n");
  
}

bool wumpus::encounter(Player& p){
    if (p.lucky_ring > 0){
        p.eaten = false;
        p.lucky_ring -= 1;
    } else {
        p.eaten = true;
    }
    return false;
}

void wumpus::print()const{
    // Prints out W to symbolize the wumpus
    printw("W");
}

int wumpus::get_wumpus_row(){
    return this->wumpus_row;
}

int wumpus::get_wumpus_col(){
    return this->wumpus_col;
}

void wumpus::set_wumpus_row(int new_row){
    this->wumpus_row = new_row;
}

void wumpus::set_wumpus_col(int new_col){
    this->wumpus_col = new_col;
}

