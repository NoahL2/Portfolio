#ifndef PLAYER_HPP
#define PLAYER_HPP

/*
 * Funciton: Player 
 * Description: A struct for the player
 */
struct Player{
	int row;
	int col;
    bool is_confused;
    bool fell_in_pit;
    bool eaten;
    bool has_gold;
    bool escaped;
    bool through_hp;

    // Keeps track of the number of lucky ring uses
    int lucky_ring = 0;

    // keep track of number of arrows remaining
    int num_arrows = 0;
};

#endif