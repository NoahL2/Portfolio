#ifndef EVENT_HPP
#define EVENT_HPP


#include "player.hpp"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <iostream>



// Event interface
class event {
private:
	// TODO private members, if relevant
protected:
	// TODO protected members, if relevant

public:
	// TODO public members

	/*
	 * Funciton: event
	 * Description: The default constructor for the abstract event class
	 */
	event() = default;

	/*
	 * Function: percept
	 * Description: This is the virtual function for the percepts that will get
	 * 				overridden by the child classes. It is a constant
	 */
	virtual void percept() const;

	/*
	 * Function: encounter
	 * Description: This is the pure virtual function for the event encounters
	 * Parameters:
	 * 		p (Player&): A reference to the player struct
	 * Returns:
	 * 		true (boolean): If the event needs to be removed from the gameboard
	 * 		false (boolean): If the event stays on the gameboard
	 */
	virtual bool encounter(Player& p) = 0;

	/*
	 * Function: print
	 * Description: This is the pure virtual function for the event symbols.
	 */
	virtual void print() const = 0;

	/*
	 * Function: ~event
	 * Description: This is the destructor for the event class
	 */
	virtual ~event() = default;
};

#endif
