/*
 * Author: Noah Letter
 * Description: For this assignment, we were asked to create a calculator that
 * 		can add, subtract, multiple, and divide. The code is supposed
 * 		to continuously ask the user for math expressions until they
 * 		tell it to stop. Once that happens a history of the computed
 * 		values is printed to the terminal. Not the given expressions,
 * 		just the answers
 */

#include <iostream>

#include "calculator.hpp"

/*
 * Function: print_error
 * Description: Prints an error message explaining that the user supplied
 * 		an invalid arithmetic expression.
 */
void print_error() {
	std::cout << "That isn't a valid arithmetic expression." << std::endl;
}

/*
 * Function: prompt_for_arithmetic_expression
 * Description: Prompts the user for an arithmetic expression and returns
 * 		whatever text they supply, whether that text represents a valid
 * 		arithmetic expression or not (validity should be checked elsewhere;
 * 		checking validity is not this particular function's responsibility).
 * Returns: An entire line of text supplied by the user via the terminal when
 * 		prompted for an arithmetic expression
 */
std::string prompt_for_arithmetic_expression() {
	std::cout << "Enter a valid arithmetic expression: ";
	std::string user_input;
	std::getline(std::cin, user_input);
	return user_input;
}

/*
 * Function: prompt_for_retry
 * Description: Asks the user whether they'd like to enter another arithmetic
 * 		expression and returns their entire line-of-text response
 * Returns: An entire line of text supplied by the user via the terminal when
 * 		asked if they'd like to enter another arithmetic expression. If this
 * 		function returns the string "Y", then that means the user would like
 * 		to enter another arithmetic expression.
 */
std::string prompt_for_retry() {
	std::cout << "Would you like to enter another expression? Enter Y for "
		"yes: ";

	std::string user_input;
	std::getline(std::cin, user_input);
	return user_input;
}

/*
 * Function: print_history_header
 * Description: Prints the header that precedes the history of values to be
 * 		printed at the end of the program.
 */
void print_history_header() {
	std::cout << "History of computed values:" << std::endl;
}

/*
 * Function: print_history_of_values
 * Description: Prints out all the values of the solved expressions once the
 * 		user ends the loop
 * Parameters:
 * 	array[] (double): Placeholder for history_array which stores all the
 * 			  computed values
 * 	size (integer): The amount of times the loop should run. It's equal to
 * 			the amount of times the user inputs a valid math
 * 			expression.
 */
void print_history_of_values(double array[], int size){
	for (int i = 0; i < size; i++) {
        	std::cout << array[i] << std::endl;
        }
}

int main() {
	// TODO Create array to represent history of at most 100 computed values
	// (and a separate variable to keep track of the number of elements that
	// have been added to it so far)
	int history_amount = 0;
	double history_array[100];
	std::string go_again;
	do {
		std::string expression = prompt_for_arithmetic_expression();

		// Check if expression is valid by using the is_valid_expression
		// function, to be defined in calculator.cpp
		if (is_valid_expression(expression)) {
			
			// Expression is valid. Compute its value by using the
			// compute_value function, to be defined in calculator.cpp.
			double value = compute_value(expression);
	
			// Print value
			std::cout << value << std::endl;

			// TODO Append value to array containing history of computed values
			// and increment the array's corresponding size variable
			//std::getline(std::cin, history_array[history_amount]);
			
			history_array[history_amount] = value;
                        history_amount++;	

			go_again = prompt_for_retry();
		} else {
			std::cout << "That isn't a valid arithmetic expression." <<
				std::endl;
			go_again = "Y";
		}
	} while(go_again == "Y");

	// Print history header
	std::cout << std::endl;
	print_history_header();

	// TODO Print history of computed values (you should do this by calling
	// another function here, which you'll need to define above this main()
	// function)

	print_history_of_values(history_array, history_amount);
}
