#include <iostream>

/*
 * THIS IS A HELPER FUNCTION. YOU AREN'T REQUIRED TO USE IT, AND YOU CAN
 * MODIFY IT IF YOU WANT, BUT I STRONGLY RECOMMEND THAT YOU USE IT AS-IS.
 * YOU MAY FIND IT VERY HELPFUL.
 * Function: is_number
 * Description: Determines whether a given string holds a valid numeric value
 * Returns: True if the given string holds a valid numeric value, or false
 * 		otherwise. If this function returns true, it's safe to use std::stod()
 * 		on the string to convert it to a number (double) afterwards. Otherwise,
 * 		the given string does not contain a valid numeric value, and attempting
 * 		to use std::stod() on the string may crash your program.
 */
bool is_number(std::string str) {
	// A valid number must contain at least one digit and at most one
	// decimal point
	int num_digits = 0;
	int num_points = 0;
	for (int i = 0; i < str.length(); i++) {
		bool is_point = str.at(i) == '.';
		// A negative sign is a dash at the beginning of the string
		bool is_negative_sign = str.at(i) == '-' && i == 0;
		bool is_number = str.at(i) >= '0' && str.at(i) <= '9';

		if (is_point) {
			// If the character is a decimal point, increment
			// the number of points found, and return false if
			// it's greater than 1
			num_points++;
			if (num_points > 1) {
				return false;
			}
		}
		if (is_number) {
			// If the character is a digit, increment the number of
			// digits found
			num_digits++;
		}

		// If the character isn't any of the three valid possibilities,
		// return false, immediately ending the function
		if (!is_point && !is_negative_sign && !is_number) {
			return false;
		}
	}

	// Return true only if at least one digit was found
	return num_digits > 0;
}

/*
 * Function: is_operator
 * Description: Determines whether a index in the expression string is a
 * 		mathmatical operator.
 * Perameters:
 * 	str (string): Placeholder for later variable that is equal to the place
 * 		      in the string that the function is checking
 * Returns:
 * 	true (boolean): If the place it checks contains an operator
 * 	false (boolean): If the place it checks does not contain an operator
*/
bool is_operator(std::string str){
	if (str == "+" || str == "-" || str == "*" || str == "/"){
		return true;
	} else {
		return false;
	}
}

/*
 * THIS IS A REQUIRED FUNCTION. YOU MAY NOT ALTER ITS HEADER (NAME, PARAMETERS,
 * OR RETURN TYPE) IN ANY WAY.
 * Function: is_valid_expression
 * Description: Determines whether a given string holds a valid arithmetic
 * 		expression, as defined in the assignment document.
 * Parameters:
 * 		expression (std::string): A string holding the expression to be checked
 * 			for validity.
 * Returns: True if the given string holds a valid arithmetic expression, or
 * 		false otherwise.
 *
 * For example, is_valid_expression("1 + 3 * 4") should return true, but
 * is_valid_expression("1+3*4") should return false (notice the lack of spaces;
 * see the assignment document for an explanation of what constitutes a valid
 * arithmetic expression for this assignment).
 */
bool is_valid_expression(std::string expression) {
	// TODO Complete this function. You may create other functions above and have
	// this function call them, if you'd like (you probably should for the sake
	// of the course's style guidelines)

	bool expect_number = true;
	while(!expression.empty()){
		int find_space = expression.find(" "); 
		if (expression.find(" ") == -1){
			if (is_number(expression)){
				return true;
			} else {
				return false;
			}
		}

		// Token becomes equal to any character inbetween 2 spaces
		std::string token = expression.substr(0, find_space);
		if (expect_number){
			if (!is_number(token)){
				return false;
			} else {

				// Changes expect_number to false because the
				// next character in the string after a number
				// and a space should be an operator
				expect_number = false;
				
				// After token is found and gets checked for
				// whether it's a number or an operator, it
				// gets erased so that the next character in
				// the string becomes token 0
				expression.erase(0, token.length() + 1);
			}
		} else {
			if (!is_operator(token)){
				return false;
			} else {
				expression.erase(0, token.length() + 1);
				expect_number = true;
			}
		} 
	
	}
	return false;
}

/*
 * Function: doing_math
 * Description: This function does the actual calculations
 * Parameters:
 * 	number_1 (double): The first number in the expression string. Changes
 * 			   to next number in the expression once
 * 			   expression.erase removes the previous numbers. 
 *	number_2 (double): The second number in the expression string Changes
 *                         to next number in the expression once
 *                         expression.erase removes the previous numbers.
 *	op (string): the operator inbetween number_1 and number_2
 * Returns:
 * 	total_value (double): The number that the user's equation equals 
 */
double doing_math (double number_1, double number_2, std::string op){
	double total_value;
	if (op == "+"){
		total_value = number_1 + number_2;
	} else if (op == "-"){
		total_value = number_1 - number_2;
	} else if (op == "*"){
		total_value = number_1 * number_2;
	} else if (op == "/"){
		total_value = number_1 / number_2;
	}
	return total_value;
}



/*
 * THIS IS A REQUIRED FUNCTION. YOU MAY NOT ALTER ITS HEADER (NAME, PARAMETERS,
 * OR RETURN TYPE) IN ANY WAY.
 * Function: compute_value
 * Description: Computes and returns the value of the given arithmetic
 * 		expression. This function should ASSUME that the given string is indeed
 * 		a valid arithmetic expression. That is, your program should check whether
 * 		a string contains a valid arithmetic expression (e.g., using your
 * 		is_valid_expression function) BEFORE passing it into this function.
 * Parameters:
 * 		expression (std::string): A string holding the arithmetic expression
 * 			to be evaluated.
 * Returns (double): The value of the given arithmetic expression, computed
 * 		according to the rules described in the assignment document
 *
 * For example: compute_value("1 + 3 * 4") should return 16, assuming you don't
 * complete the order-of-operations extra credit.
 */
double compute_value(std::string expression) {
	// TODO Complete this function. You may create other functions above and have
	// this function call them, if you'd like (you probably should for the sake
	// of the course's style guidelines)
	char find_space = expression.find(" ");
	std::string token = expression.substr(0, find_space);
	double running_amount = std::stod(token);
	expression.erase(0, token.length() + 1);
	while (!expression.empty()){
		int space = expression.find(" ");
		std::string op = expression.substr(0, space);
		expression.erase(0,2);
		space = expression.find(" ");
		double num;
		if(space == -1){
			num = std::stod(expression);
			expression = "";
		} else {
			std::string number_string = expression.substr(0, space);
			num = std::stod(number_string);

			// After number_string is found and it gets stored in
			// the num variable, that character in the expression
			// gets erased so that the next character in the string
			// becomes the new first number in the expression
			expression.erase(0, number_string.length() + 1);
		}
	running_amount = doing_math(running_amount, num, op);
	}
	return running_amount;
}
