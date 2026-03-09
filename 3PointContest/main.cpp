// In some assignments, you will be provided with a bit of "skeleton code"
// to get you started. However, this assignment is largely geared toward
// getting you up to speed on the basics of C++ programming, so there's very
// minimal starter code here for you.

// All of your programming assignments' driver files (i.e., the .cpp file
// containing the main() function) should have a program header at the
// top. Fill in the program header below:

/*
 * Author: Noah Letter
 * Program description: This is a two player basketball shooting game. It takes two
 * 			inputs from the users, the position of a money ball rack and the
 * 			user's shooting capability. It then simulates a shooting contest
 * 			from 7 different locations then displays the results. 
 * 			There are 4 normal racks with 4 balls worth 1 point each and 1
 * 			money ball worth 2 points. Then there's 1 money ball rack
 * 			situated wherever the user chooses, each ball is worth 2 points.
 *			Lastly there's 2 starry ball racks located between racks 2 and 3
 *			and 3 and 4, each starry ball is 3 points. Whether or not the
 *			shot is made is determined by the user's shooting capability and
 *			a random number. The code generates a random number and compairs
 *			it to the shooting capability, if the random number is than or
 *			equal to the shooting ability, then the shot is made. After
 *			player one goes, it repeats the process with player two, using
 *			new inputs from the second person. Once both players have gone,
 *			it then declares a winner and asks if they want to play again, if
 *			yes it starts from the top, if no it quits.
 */

// Recall: this is the syntax for importing / including system-installed
// header files in C++. The <iostream> header file gives you access to
// input / output (I/O) tools, like std::cout, std::cin, and std::endl, so
// that your program can interface with the terminal
#include <iostream>


// You'll also need <cstdlib> and <ctime> to use srand() and rand() for
// pseudorandom number generation (PRNG)
#include <cstdlib>
#include <ctime>

// TODO: Create many other functions here (you'll want several of them to
// satisfy the course's style guidelines: 
// https://web.engr.oregonstate.edu/~songyip/Teaching/CS16X/cpp_style_guideline.pdf)

// Recall: This is the main() function. It's the entrypoint to your program
// (i.e., it is where your program will both start and end).

using namespace std;

/*
 * Function: welcome
 * Description: Prints out message welcoming players
 */
void welcome(){
	cout << "Welcome to the basketball shooting contest" << endl;
	cout << endl;
}

/*
 * Function: error_handling_for_money_ball_rack
 * Description: Takes the user's input for where they want the money ball rack to be
 * 		then it checks if it's a valid input. If it's not then it prints out
 * 		an error message and sets the function to false which is later used to
 * 		continually reprompt the user for a valid input while this function is
 * 		false. If the input is valid then it sets the function to true.
 * Parameters:
 * 		rack (int): The user's input for the position of the money ball rack.
 * Returns:
 * 		false (boolean): If the user's input is invalid (less than 1 or greater
 * 				than 5)
 * 		true (boolean): If the user's input is valid (Greater than or equal to 1
 * 				and less than or equal to 5)
 *
 */
bool error_handling_for_money_ball_rack(int rack){
	if (rack < 1 || rack > 5){
		cout << "Sorry, that is not a valid input" << endl;
		return false;
	} else { 
		return true;
	}	
}

/*
 * Function: error_handling_for_shooting_ability
 * Description: Takes the user's input for their shooting capability then it checks if 
 * 		it's a valid input. If it's not then it prints out an error message and
 * 		sets the function to false which is later used to continually reprompt
 * 		the user for a valid input while this function is false. If the input is
 * 		valid then it sets the function to true.
 * Parameters:
 *              shooting (int): The user's input for their shooting capability
 * Returns:
 *              false (boolean): If the user's input is invalid (Less than 1 or greater
 *              		 than 99)
 *              true (boolean): If the user's input is valid (Greater than or equal to 1
 *              		and less than or equal to 99)
 *
 */
bool error_handling_for_shooting_ability(int shooting){
	if (shooting < 1 || shooting > 99){
                cout << "Sorry, that is not a valid input";
                return false;
        } else {
                return true;
        }		
}

/*
 * Function: money_ball_rack_postion
 * Description: Asks the user where they would like to put their money ball rack then
 * 		stores that in a int variable. It uses the error handling function to
 * 		check if it's valid, and repeats if it's not.
 * Return:
 * 		rack (int): The placement of the user's money ball rack
 */
int money_ball_rack_position(){
	int rack;
	bool error;
	
	do{
		cout << "Where would you like the placement of your money ball rack to "
			"be? (1-5 inclusive): ";
		cin >> rack;
		error = error_handling_for_money_ball_rack(rack);
	} while (error == false);

	return rack;
}

/*
 * Function: shooting_capability
 * Description: Prompts the user for their shooting capability and stores that in an int
 * 		variable. It uses the error handling function to check if it's valid. If
 * 		it's not then it continually repeats until it is.
 * Returns:
 * 		shooting (int): The user's shooting capability
 */
int shooting_capability(){
	int shooting;
	bool error;

	do{
		cout << "Please enter your shooting capability "
			"(1-99 inclusive): ";
		cin >> shooting;
		error = error_handling_for_shooting_ability(shooting);
		cout << endl;
	} while (error == false);

	return shooting;
}

/*
 * Function: simulate_shots
 * Description: Creates a random number in between 1 and 99 and compares it to the
 * 		user's shooting capability. If the random number less than or equal to
 * 		the shooting capability then it sets an int varible to 1, which means the
 * 		shot was made. If it's greater then the shooting capability then it sets 
 * 		the variable to 0 meaning the shot missed.
 * Parameters:
 * 		shooting_ability (int): The integer that the user decided was their
 * 					shooting capability.
 * Returns:
 * 		outcome (int): Whether or not the user made the shot.
 */
int simulate_shots(int shooting_ability){
        int outcome = -1;
        int shot_outcome = -1;
        int random_outcome = -1;

        shot_outcome = shooting_ability % 100;
        random_outcome = rand() % 100;
        if (shooting_ability >= random_outcome){
                outcome = 1;
        } else {
                outcome = 0;
        }

        return outcome;
}

/*
 * Function: rack_symbols
 * Description: It takes the array for the 5 racks and runs through each array index,
 * 		If it sees a 0 it populates a second array in the same position with an
 * 		underscore to show that the shot missed. If it sees a 1 then it populates
 * 		that position in the second array with an "X" to show that the shot was
 * 		made. It also checks for the money ball rack, each shot made during the 
 * 		money ball rack is displayed by an "M". Also every 5th shot of the normal
 * 		racks are money balls, if made, they are also displayed by an "M".
 * Parameters:
 * 		money_ball_rack (int): The position of the money ball rack.
 * 		number_array (int array): A 5x5 array of ones, twos, and zeros showing if 
 * 					  the shot was made or not.
 * 		symbol (char array): A 5x5 array of X's, M's, and underscores showing if 
 * 				     the shot was made or not.
 */
void rack_symbols(int money_ball_rack,int number_array[5][5],char symbol[5][5]){
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (number_array[i][j] == 0){
				symbol[i][j] = '_';
			} else {
				if (i+1 == money_ball_rack){
					symbol[i][j] = 'M';
				} else if (j == 4){
					symbol[i][j] = 'M';
				} else {
					symbol[i][j] = 'X';
				}
			}
		}
	
	} 
}

/*
 * Function: starry_symbol
 * Description: This takes the array for the starry ball racks and populates a second
 * 		array with symbols instead of numbers. If it there's a zero in the first
 * 		array, it puts an underscore in the same position in the second array. If
 * 		it sees anything else, it puts an "S" to show that the shot was made.
 * Parameters: 
 *		starry (int array): The array of 3s and 0s that show if a shot was made
 *				    or not
 *		starry_characters (character array): An array of symbols that replaces
 *						     the array of numbers.
 */
void starry_symbol(int starry[2], char starry_characters[2]){
	for (int i = 0; i < 2; i++){
		if (starry[i] == 0){
			starry_characters[i] = '_';
		} else {
			starry_characters[i] = 'S';
		}
	}
}

/*
 * Function: total_score
 * Description: Checks each position of the integer array, if it sees a 0 it adds 0 
 * 		points to a running total, if it sees a 1 it adds 1 to a running total,
 * 		if it sees a 2, it adds 2 to a running total.
 * Parameters:
 * 		money_ball_rack (int): The position of the money ball rack
 * 		number_array (int array): A 5x5 array of ones, twos, and zeros showing if
 *                                        the shot was made or not.
 * Returns:
 * 		total_score (int): The player's total score for all the racks 
 */
int total_scores(int money_ball_rack, int number_array[5][5], int starry_scores){
	int total_score = 0;
	for (int i = 0; i < 5; i++){
        	for (int j = 0; j < 5; j++){
                	if (number_array[i][j] == 0){
                                total_score += 0;
                        } else {
                                if (i+1 == money_ball_rack){
                                        total_score += 2;
					number_array[i][j] = 2;
                                } else if (j == 4){
                                        total_score += 2;
					number_array[i][j] = 2;
                                } else {
                                        total_score += 1;
                                }
                        }
                }
        }
	total_score += starry_scores;
	return total_score;
}

/*
 * Function: starry_scores
 * Description: This checks if the shot was made or missed. If the shot was made then it
 * 		adds 3 to a running total, if it missed then it adds a 0.
 * Parameters:
 * 		starry_ball (int array): The array of numbers that show if the shot was
 * 					 made or missed.
 * Return: 
 * 		starry_score: The running total of the starry balls 
 */
int starry_scores(int starry_ball[2]){
	int starry_score = 0;
	for (int i = 0; i < 2; i++)
		if (starry_ball[i] == 0){
			starry_ball[i] = 0;
			starry_score += 0;
		} else {
			starry_ball[i] = 3;
			starry_score += 3;
		}
	return starry_score;
}

/*
 * Function: array_of_numbers
 * Description: Populates a 5x5 array with the shot outcomes as numbers. 1 for a normal
 * 		shot, 2 for a money ball shot, and 0 for a miss.
 * Parameters:
 * 		number_array (int array): A 5x5 array of ones, twos, and zeros showing if
 *                                        the shot was made or not.
 *		shooting_ability (int): The integer that the user decided was their
 *                                      shooting capability.
 * Returns:
 * 		number_array (int array): A 5x5 array of ones, twos, and zeros showing if
 *                                        the shot was made or not.
 */
int array_of_numbers(int number_array[5][5], int shooting_ability, int starry[2]){
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                        int shot_one = simulate_shots(shooting_ability);
                        number_array[i][j] = shot_one;
                }
        }
	
	for (int i = 0; i < 2; i++){
		int starry_shot = simulate_shots(shooting_ability);
                starry[i] = starry_shot;
      	}

	return number_array[5][5];
}

/*
 * Function: display_array
 * Description: Prints out the racks with the characters that show if the shot was made
 * 		or not instead of the numbers and takes the numbers in the from each rack
 * 		and adds it to a running total so that the points for each rack can be
 * 		displayed
 * Parameters:
 * 		number_array (int array): A 5x5 array of ones, twos, and zeros showing if
 *                            		  the shot was made or not
 *              characters (char array): A 5x5 array of X's, M's, and underscores showing
 *              			 if the shot was made or not
 * Returns:
 * 		rack_total: The total points for each rack
 */
int display_array(int number_array[5][5],char characters[5][5], int starry_num[2], 
		char starry[2]){
        int rack_total = 0;
        for (int i = 0; i < 5; i++){
		rack_total = 0;
                if (i == 2 || i == 3){
			cout << "Starry: " << starry[i-2];
			rack_total += starry_num[i-2];
			cout << "	  | " << rack_total << " points" << endl;
		}
		cout << "Rack " << i+1 << ": ";
		rack_total = 0;
		for (int j = 0; j < 5; j++){
			cout << characters[i][j] << " ";
                        rack_total += number_array[i][j];
                }
        cout << "| " << rack_total << " points" << endl;
	}
	return rack_total;
}

/*
 * Function: play_again
 * Description: Asks the users if they would like to play again. If they enter a 1 it
 * 		sets the function to true. If they enter anything else it sets it to
 * 		false.
 * Returns:
 * 		true (boolean): If the users enter 1 to play again
 * 		false (boolean): If the users enter 0 to not play again 		 
 */
bool play_again(){
        int answer;
        cout << "Would you like to play again? (1-yes, 0-no): ";
        cin >> answer;
        if (answer == 1){
                return true;
        } else{
                return false;
        }
}


int main() {
	// This line seeds your PRNG. You don't need to call srand() anywhere else.
	// After it's been called, you can then proceed to use the rand() function
	// to generate pseudorandom numbers at any point in your program.
	srand(time(nullptr));

	// TODO: complete the main function, having it call other functions (and
	// perhaps having those functions call other functions, and so on) to
	// complete the program as described in the assignment description document
	// on Canvas.
	
	// Declares a boolean variable to later be initalized to the play_again function
	bool continue_playing;

	int starry_rack[2];
	char starry_character[2];
	int rack_array[5][5];
	char character_array[5][5]; 
	
	do{
		welcome();

		for (int i = 0; i < 2; i++){
			cout << "Player " << i+1 << ":" << endl;
		
			// Intializes and calls the function the asks user for position of
			// the money ball rack
			int money_ball = money_ball_rack_position();
				
			// Intializes and calls the function that asks user for their
			// shooting capability	
			int shooting_ability = shooting_capability();
	
			// Initializes and calls the function that populates an array of
			// numbers with numbers that show if the shot was made or not
			int initialization = array_of_numbers(rack_array, 
				shooting_ability, starry_rack);		
			
	       		// Initializes and calls the function looks through the starry
			// ball array and sees if the shot was made or not. Then it adds
			// the correct score to a running total if the shot was made		
			int starry_score = starry_scores(starry_rack);
			
			// Populates an array with symbols based on if the starry ball
			// was made or not
                        starry_symbol(starry_rack, starry_character);
			
			// Initializes and calls the function that adds all the racks
			// scores to a running total then prints out the score
			int score = total_scores(money_ball, rack_array, starry_score);
			
			// Populates an array with symbols based on the normal rack
			// scores
			rack_symbols(money_ball, rack_array, character_array);

			//print the racks out 
			int print_array = display_array(rack_array,character_array, 
					starry_rack, starry_character);		
			
			cout << "Player " << i+1 << "'s total score: " << score << endl;
			cout << endl;
		}

		continue_playing = play_again();

	} while (continue_playing == true);
}
