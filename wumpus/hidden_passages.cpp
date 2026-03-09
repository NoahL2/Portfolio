#include "hidden_passages.hpp"



void hidden_passages::percept() const{
    printw("You hear water dripping.\n");
}

bool hidden_passages::encounter(Player& p){
    p.through_hp = true;
    
    return false;
}

void hidden_passages::print()const{
    // Prints out the letter H to symbolize the hidden passages
    printw("H");
}

int hidden_passages::get_first_hidden_passages_row(){
    return this->first_hidden_passages_row;
}

int hidden_passages::get_first_hidden_passages_col(){
    return this->first_hidden_passages_col;
}

void hidden_passages::set_first_hidden_passages_row(int new_row){
    this->first_hidden_passages_row = new_row;
}

void hidden_passages::set_first_hidden_passages_col(int new_col){
    this->first_hidden_passages_col = new_col;
}

int hidden_passages::get_second_hidden_passages_row(){
    return this->second_hidden_passages_row;
}

int hidden_passages::get_second_hidden_passages_col(){
    return this->second_hidden_passages_col;
}

void hidden_passages::set_second_hidden_passages_row(int new_row){
    this->second_hidden_passages_row = new_row;
}

void hidden_passages::set_second_hidden_passages_col(int new_col){
    this->second_hidden_passages_col = new_col;
}