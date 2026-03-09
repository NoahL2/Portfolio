#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"
// #include "gold.hpp"
// #include "bat_swarm.hpp"
// #include "bottomless_pit.hpp"
// #include "wumpus.hpp"
// #include "escape_rope.hpp"
// #include "arrow.hpp"

// Room interface
class Room {
private: 
	// TODO private members

	// Pointer to the event class
	event* room_event = nullptr;
public:
	// TODO public members

	/*
	 * Function: Room()
	 * Descrition: The default constructor of the room class
	 */
	Room()=default;


	// Room(int);

	/*
	 * Function: ~Room
	 * Description: This is the destructor for the Room class. If the event pointer is
	 * 				not a null pointer then it deletes the event that it's pointing to
	 * 				and sets it to null ptr
	 */
	~Room();

	/*
	 * Function: operator=
	 * Description: This is the AOO
	 * Parameters:
	 * 		other (Room&): A reference to the move objects
	 * Returns:
     * 		*this: The calling object
	 */		
	Room& operator=(const Room& other);

 	/*
	 * Function: Room
	 * Description: This is the copy constructor. This deep copies the move member
	 * 				variables
	 * Parameters: 
	 * 		other (Room&): A reference to the move member variables
	 */
	Room(const Room& other);

	/*
	 * Function: room_is_empty
	 * Description: Checks to see if the event pointer is a null pointer
	 * Returns:
	 * 		true (bool): If the event pointer is a null pointer
	 * 		false (bool): If the event pointer is not a null pointer
	 */
	bool room_is_empty();

	/*
	 * Function: print
	 * Description: Prints out the symbol of the corret event 
	 */
	void print()const;

	/*
	 * Function: percept
	 * Description: Prints out the percept of the corret event 
	 */
	void percept()const;

	/*
	 * Function: set_event
	 * Description: Sets the event pointer to an event child class object 
	 */
	void set_event(event* e);

	/*
	 * Function: get_event
	 * Description: Gets the correct event
	 * Returns:
	 * 		room_event: The current event at or near the players location
	 */
	event* get_event() const;

	
};

#endif
