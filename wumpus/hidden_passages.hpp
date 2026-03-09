#ifndef HIDDEN_PASSAGES_HPP
#define HIDDEN_PASSAGES_HPP

#include "event.hpp"

// TODO Bottomless Pit interface (define the hidden_passages class and declare
// its member functions below)

class hidden_passages : public event {
    private:
        int first_hidden_passages_row;
        int first_hidden_passages_col;
        int second_hidden_passages_row;
        int second_hidden_passages_col;
    public:

        /*
         * Funciton: hidden_passages
         * Description: The default constructor for the hidden passage class
         */
        hidden_passages() = default;

        /*
         * Function: percept
         * Description: Print out the percept of the hidden passage event
         */
        void percept() const;

        /*
         * Funciton: encounter
         * Description: If the player enters a room with a hidden passage they get
         *              teleported to the other hidden passage room
         * Parameters:
         *      p (Player&): A reference to the player struct
         * Returns:
         *      false (bool): Returns false because the event stays on the gameboard
         */
        bool encounter(Player& p);

        /*
         * Funciton: print
         * Description: Prints out the letter H
         */
        void print() const;

        /*
         * Funciton: ~hidden_passages
         * Description: The destuctor for the hidden_passages class
         */
        ~hidden_passages() = default;

        int get_first_hidden_passages_row();

        int get_first_hidden_passages_col();

        void set_first_hidden_passages_row(int new_row);

        void set_first_hidden_passages_col(int new_col);

        int get_second_hidden_passages_row();

        int get_second_hidden_passages_col();

        void set_second_hidden_passages_row(int new_row);

        void set_second_hidden_passages_col(int new_col);


};


#endif