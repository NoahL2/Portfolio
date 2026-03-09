#include "bat_swarm.hpp"


// TODO Bat Swarm implementation (define bat_swarm member functions below)
void bat_swarm::percept() const{

    printw("You hear screeching.\n");

}

bool bat_swarm::encounter(Player& p){
    
    // If the player walks through a bat swarm they get confused
    p.is_confused = true;
    return false;
}



void bat_swarm::print()const{
    // Prints out the letter B to symbolize a bat swarm
    printw("B");
}

 