#include <iostream>
#include <vector>

#include "game.hpp"
// #include "gold.hpp"
// #include "bat_swarm.hpp"
// #include "bottomless_pit.hpp"
// #include "wumpus.hpp"
// #include "escape_rope.hpp"
// #include "arrow.hpp"
// #include "lucky_ring.hpp"
// #include "hidden_passages.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::string;

// game implementation


game::game(int width, int height, bool debug) :
		width(width),
		height(height),
		debug(debug) {

    player.is_confused = false;
    player.fell_in_pit = false;
    player.eaten = false;
	player.has_gold = false;
	player.escaped = false;


	// TODO Create the game board: 2D vector of room objects
	for (int i = 0; i < height; i++){
		vector<Room> temp_vector(width);
		room_vector.push_back(temp_vector);
	}
	// Calls the funciton that puts the events into the room vector
	create_events();

	// Creates a random height on the gameboard
	int random_height = create_rand_height();

	// Creates a random width on the gameboard
	int random_width = create_rand_width();

	// Creates another set of a random height and width if the above set already contains
	// a pointer 
	while (room_vector.at(random_height).at(random_width).get_event() != nullptr){
		random_height = create_rand_height();
		random_width = create_rand_width();
	}
		// Sets the players location to the random height and width
		player.row = random_height;
		player.col = random_width;

	// Puts the escape rope at the spot where the player started
	room_vector.at(player.row).at(player.col).set_event(new escape_rope);

	// TODO Randomly insert events (2 bat_swarms, 2 bottomless_pits,
	// 1 wumpus, 1 gold, 2 arrows, 1 escape rope) into the board
}

int game::create_rand_height(){
	// This creates a random number height from the heigth of the gameboard
	int random_height = rand() % this->height;
	return random_height;
}

int game::create_rand_width(){
	// This finds a random number from the width of the gameboard 
	int random_width = rand() % this->width;
	return random_width;
}

void game::display_game() const{
	// cout << endl << endl;
	// cout << "Arrows remaining: " << this->num_arrows << endl;
    printw("\n \n");
    printw("Arrows remaining: %d\n", player.num_arrows);
	printw("Lucky rings remaining: %d\n", player.lucky_ring);

	string row_border = "--";
	for (int i = 0; i < this->width; ++i) {
		row_border += "-----";
	}

	// cout << row_border << endl;
    printw("%s\n", row_border.c_str());
	for (int i = 0; i < this->height; ++i) {
		// cout << "||";
        printw("||");
		for (int j = 0; j < this->width; ++j) {
			// The first char indicates whether there is a player in the room
			// at row index i, column index j. TODO If the room contains the
			// player, print an asterisk ("*")

			if (player.row == i && player.col == j){
				// cout << "*";
                printw("*");	
			} else {
				// cout << " ";
                printw(" ");
			}

			// If the player chooses to play in debug mode
			if (debug){
				// If the vector at index i and j is not a null pointer
				if (room_vector.at(i).at(j).get_event() != nullptr){
					// Prints out the symbol for the event that is at the vector index
					room_vector.at(i).at(j).print();
				} else {
					printw(" ");
				}
			}



			// The next char indicates the event in the room.
			
			// TODO If debug mode is disabled OR the room at location <i, j>
			// does not have an event, print a space (" ")
			// For example:
			// if (!this->debug || <i, j> ROOM DOES NOT HAVE EVENT) {
			// 	cout << " ";
			// }
			//
			// TODO else, print the room's debug symbol. There are a few ways to
			// do this. You can use polymorphism, or an event could have a
			// char debug_symbol member variable and some sort of
			// get_debug_symbol() member function that you could call here
			// to get the character and print it.


			// cout << " ||";
            printw(" ||");
		}
		// cout << endl;
		// cout << row_border << endl;
        printw("\n");
        printw("%s\n", row_border.c_str());
	}

	//example output (when finished): 
	// ----------------------
	// || P || G || P ||   ||
	// ----------------------
	// ||   || W ||   || S ||
	// ----------------------   
	// ||   ||   ||   || S ||
	// ----------------------   
	// ||*  ||   ||   ||   ||
	// ----------------------
	refresh();

}

bool game::check_win() const{
	// TODO Delete the below placeholder code. Return true if the player
	// has won the game. Return false otherwise.

	// player.escaped is only true if the player has the gold and has made it back to
	// the esacpe rope

	// bool is_dead = wumpus_location.get_is_wumpus_dead();

	if (player.escaped || wumpus_is_dead == true){
		return true;
	}

	return false;
}

bool game::check_lose() const{
	// TODO Delete the below placeholder code. Return true if the player
	// has lost the game. Return false otherwise.

	// The player loses if they fall into a pit or is eaten by the wumpus
	if (player.fell_in_pit || player.eaten){
		return true;
	}

	return false;
}

bool game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction) {
	// TODO Delete the below placeholder code. Return true if the player can
	// move in the given direction ('w' for up, 'a' for left, 's' for down,
	// 'd' for right). Return false otherwise. The player can move in the
	// given direction so long as it wouldn't cause them to move off the
	// grid.

	if (direction == 'w'){
		// If the player trys to move up into a wall
		if (player.row - 1 < 0){
			// Returns false because they can't go through a wall
			return false;
		}
	} else if (direction == 's') {
		// If the player trys to move down into a wall
		if (player.row + 1 > height - 1){
			// Returns false because they can't go through a wall
			return false;
		}
	} else if (direction == 'a'){
		// If the player trys to move left into a wall
		if (player.col - 1 < 0 ){
			// Returns false because they can't go through a wall
			return false;
		}
	} else if (direction == 'd'){
		// If the player trys to move right into a wall
		if (player.col + 1 > width - 1){
			// Returns false because they can't go through a wall
			return false;
		}
	}

	return true;
}

bool game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return player.num_arrows > 0;
	}
	return false;
}

void game::print_action_error(char action) {
	if (this->is_direction(action)) {
        printw("You can't move in that direction! \n");
	} else if (action == 'f') {
        printw("You're out of arrows! \n");
	} else {
        printw("\n That's an invalid input! \n \n");
	}
}

char game::get_player_action() {

	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		// cout << endl << endl << "What would you like to do?" <<
		// 	endl << endl;
        printw("\n \n What would you like to do? \n \n");

		// cout << "w: move up" << endl;
        printw("w: move up \n");

		// cout << "a: move left" << endl;
        printw("a: move left \n");

		// cout << "s: move down" << endl;
        printw("s: move down \n");

		// cout << "d: move right" << endl;
        printw("d: move right \n");

		// cout << "f: fire an arrow" << endl;
        printw("f: fire an arrow \n");

		// Refreshes the screen to show show the new gameboard
		refresh();
		// Gets the direction and stores it in action
        action = getch();
		// clears the screen
		wclear(stdscr);
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			// cout << endl << "That's an invalid input!" <<
			// 	endl << endl;
            printw("\n That's an invalid input! \n \n");
		}
		first = false;

		// cout << endl << endl <<
		// 	"What direction would you like to fire the arrow?" << endl <<
		// 	endl;
        printw("\n \nWhat direction would you like to fire the arrow?? \n \n");

		// cout << "w: up" << endl;
        printw("w: up \n");

		// cout << "a: left" << endl;
        printw("a: left \n");

		// cout << "s: down" << endl;
        printw("s: down \n");

		// cout << "d: right" << endl;
        printw("d: right \n");

		refresh();
        direction = getch();
		wclear(stdscr);
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::move_up() {
	// TODO Delete the below placeholder code. Move the player up one
	// space in the grid, however you choose to do that.

	player.row -= 1;
}

void game::move_down() {
	// TODO Delete the below placeholder code. Move the player down one
	// space in the grid, however you choose to do that.

	player.row += 1;
}

void game::move_left() {
	// TODO Delete the below placeholder code. Move the player left one
	// space in the grid, however you choose to do that.

	player.col -= 1;
}

void game::move_right() {
	// TODO Delete the below placeholder code. Move the player right one
	// space in the grid, however you choose to do that.

	player.col += 1;
}

void game::move(char direction) {

	// Creates an array of direction keys for random movement
	char confused_array[4] = {'w', 'a', 's', 'd'};


	if (player.is_confused){
		do{
			// creates a random number between 0 and 3 inclusive
			int random_move = rand() % 4;

			// Sets the direction to a random index of the array using the random number
			direction = confused_array[random_move];

			// Sets player confused status back to false
			player.is_confused = false;

		// Repeats the proccess if the direction it moves is not valid
		} while (!can_move_in_direction(direction));
	}

	if (direction == 'w') {
		this->move_up();
	} else if (direction == 'a') {
		this->move_left();
	} else if (direction == 'd') {
		this->move_right();
	} else {
		this->move_down();
	}
}

void game::fire_arrow_up() {
	// TODO Delete the below placeholder code. Fire the arrow upward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses

	// if wumpus is three spaces above player it dies
	// if else it moves

	if (player.row - 3 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;

	} else if (player.row - 2 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;
		
	} else if (player.row - 1 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;
	}
}

void game::fire_arrow_down() {
	// TODO Delete the below placeholder code. Fire the arrow downward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	
	if (player.row + 3 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;

	} else if (player.row + 2 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;
		
	} else if (player.row + 1 == wumpus_location.get_wumpus_row()){
		wumpus_is_dead = true;
	}
}

void game::fire_arrow_left() {
	// TODO Delete the below placeholder code. Fire the arrow leftward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	
	if (player.col - 3 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;

	} else if (player.col - 2 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;
		
	} else if (player.col - 1 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;
	}

	// cout << "game::fire_arrow_left is not implemented..." << endl;
}

void game::fire_arrow_right() {
	// TODO Delete the below placeholder code. Fire the arrow rightward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses

	
	if (player.col + 3 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;

	} else if (player.col + 2 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;
		
	} else if (player.col + 1 == wumpus_location.get_wumpus_col()){
		wumpus_is_dead = true;
	} 
	// else {
	// 	wumpus_is_also_dead = false;
	// }

	// cout << "game::fire_arrow_right is not implemented..." << endl;
}

void game::fire_arrow(char direction) {
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 'd') {
		this->fire_arrow_right();
	} else {
		this->fire_arrow_down();
	}

	player.num_arrows--;
}

void game::play_game(){
	while (!this->check_win() && !this->check_lose()) {
		// Print game board
		this->display_game();

		// TODO Display precepts around player's location

		print_percepts();

		// Ask player for their action
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
		}

		// move_wumpus();

		// TODO If the user is on a space with an event, trigger its encounter


		// Creates a boolean for if the event needs to be removed
		bool removes = false;

		// Creates another event point and sets it to the event at the players current
		// location 
		event* curr_event = room_vector.at(this->player.row).at(this->player.col).get_event();
		if (curr_event != nullptr){

			// encounter() returns true or false if the event needs to get removed
			removes = curr_event->encounter(player);
		}


		if (removes) {
			// If the event needs to get removed then this deletes the event
			delete curr_event;

			// sets this pointer to to null
			curr_event = nullptr;

			// sets the event pointer at this location to null
			room_vector.at(this->player.row).at(this->player.col).set_event(nullptr);
		}

		if (player.through_hp && (player.row == hp.get_first_hidden_passages_row() && 
				player.col == hp.get_first_hidden_passages_col())){
			player.row = hp.get_second_hidden_passages_row();
			player.col = hp.get_second_hidden_passages_col();
		} else if (player.through_hp && (player.row == hp.get_second_hidden_passages_row() &&
				player.col == hp.get_second_hidden_passages_col())){
			player.row = hp.get_first_hidden_passages_row();
			player.col = hp.get_first_hidden_passages_col();
		}
	}
}

void game::create_events(){
	// Creates a new event pointer vector and initializes it to the correct amount
	// of events
	vector<event*> event_vec{
	new bat_swarm,
	new bat_swarm, 
	new bottomless_pit, 
	new bottomless_pit,
	new wumpus,
	new arrow,
	new arrow,
	new gold,
	new lucky_ring,
	new hidden_passages,
	new hidden_passages,
	};
	// Gets the size of the new vector
	int event_size = event_vec.size();

	for (int i = 0; i < event_size; i++){

		// Calls the funciton that creates a random heigth on the gamboard
		int random_height = create_rand_height();

		// Calls the funciton that creates a random width on the gameboard
		int random_width = create_rand_width();

		// While the room vector at the random height and width is not a nullpointer
		while (room_vector.at(random_height).at(random_width).get_event() != nullptr){

			// Creates another random height
			random_height = create_rand_height();
			
			// Creates another random width
			random_width = create_rand_width();
		}
		// Puts the last element of the event vector into the room vectors 
		room_vector.at(random_height).at(random_width).set_event(event_vec.back());
		
		// the wumpus is the 7th event object to be added to the vector
		if (i == 6){

			// gets the row of the wumpus
			wumpus_location.get_wumpus_row();

			// gets the column of the index
			wumpus_location.get_wumpus_col();

			// sets the row to the random height that is generated for the wumpus event
			wumpus_location.set_wumpus_row(random_height);
			// sets the column to the random width that is generated for the width event
			wumpus_location.set_wumpus_col(random_width);
		}

		if (i == 0){
			hp.get_first_hidden_passages_row();
			hp.get_first_hidden_passages_col();
			hp.set_first_hidden_passages_row(random_height);
			hp.set_first_hidden_passages_col(random_width);
			hp1 = true;
		}

		if (i == 1){
			hp.get_second_hidden_passages_row();
			hp.get_second_hidden_passages_col();
			hp.set_second_hidden_passages_row(random_height);
			hp.set_second_hidden_passages_col(random_width);
			hp2 = true;
		}

		// Deletes the last element of the event vector after it is added to the
		// room vector
		event_vec.pop_back();
	}
}

void game::print_percepts(){

	if (player.row - 1 >= 0 && 
			room_vector.at(player.row - 1 ).at(player.col).get_event() != nullptr){

		// Prints the percept when the player is below an event		
		room_vector.at(player.row - 1 ).at(player.col).percept();
	} 
	if (player.row + 1 < height &&
			room_vector.at(player.row + 1 ).at(player.col).get_event() != nullptr){

		// Prints the percept when the player is above an event
		room_vector.at(player.row + 1 ).at(player.col).percept();
	} 
	if (player.col - 1 >= 0 &&
			room_vector.at(player.row).at(player.col - 1).get_event() != nullptr){

		// Prints the percept when the player is to the right of an event
		room_vector.at(player.row).at(player.col - 1).percept();
	} 
	if (player.col + 1 < width &&
			room_vector.at(player.row).at(player.col + 1).get_event() != nullptr){

		// Prints the percept when the player is to the left of an event
		room_vector.at(player.row).at(player.col + 1).percept();
	}
}

// void game::move_wumpus(){
// 	if (wumpus_is_also_dead == false){
// 		int the_wumpus_row = wumpus_location.get_wumpus_row();
// 		int the_wumpus_col = wumpus_location.get_wumpus_col();

// 		// creates a random number between 0 and 3 inclusive
// 		int random_move = rand() % 4;
// 		if (random_move == 0){
// 			room_vector.at(the_wumpus_row).at(the_wumpus_col);
// 		} else if (random_move == 1){
// 			wumpus_location.set_wumpus_row(wumpus_location.get_wumpus_row() - 1);
// 		} else if (random_move == 2){
// 			wumpus_location.set_wumpus_col(wumpus_location.get_wumpus_col() + 1);
// 		} else if (random_move == 3){
// 			wumpus_location.set_wumpus_col(wumpus_location.get_wumpus_col() - 1);
// 		}
// 	}

// }


