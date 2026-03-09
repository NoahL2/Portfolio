// TODO File block comment

// TODO If you'd like to include any other header files, do so right below
// this comment

/* 
 * Author: Noah Letter
 * Description: This is a dictionary that gives the user a definition,
 *              a URL to an audio sample, the formal pronunciation, or an
 *              example sentence of their word depending on what they want.
 *              It extracts and querys each bit of information from a
 *              dictionary API. The code ask the user for what type of
 *              information the want, then if the input is valid, it asks the
 *              user for a word. If the input is invalid, it informs the user
 *              and asks the user again to choose what info they want. Once the
 *              user provides a word it takes that word and the users previous
 *              choice and searches the API for the appropriate information. If
 *              the API doesn't have the right data, it informs the user and
 *              starts over. It continues to loop until the user chooses to
 *              exit the program.
 */

/* BEGINNING OF TEMPLATE CODE; DO NOT MODIFY */




#include <sstream>
#include <iostream>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "cpp-httplib/httplib.h"

#include "json11/json11.hpp"

const std::string DICTIONARY_API_HOST = "https://api.dictionaryapi.dev";
const std::string DICTIONARY_API_PATH_PREFIX = "/api/v2/entries/en/";

using json11::Json;

/*
 * Function: build_request_endpoint
 * Description: Builds the dictionaryapi.dev request endpoint for a given word
 * Parameters:
 * 		word (std::string): Word for which to build request endpoint
 * Returns (std::string): Request endpoint
 */
std::string build_request_endpoint(std::string word) {
	std::stringstream endpoint_ss;
	endpoint_ss << DICTIONARY_API_PATH_PREFIX;
	endpoint_ss << word;
	return endpoint_ss.str();
}

/*
 * Function: extract_definition
 * Description: Extracts the first definition available in the given
 * 		JSON response from dictionaryapi.dev.
 * Parameters:
 * 		words (json11:Json): Parsed json11::Json object of response from
 * 			dictionaryapi.dev
 * Returns (std::string): First definition available in given JSON response.
 * 		If none are available, returns an empty string.
 */
std::string extract_definition(const Json words) {
	// For each word
	const Json::array& word_arr = words.array_items();
	for (const Json& word : word_arr) {
		// Get meanings
		const Json& meanings = word["meanings"];

		// For each meaning
		const Json::array& meaning_arr = meanings.array_items();
		for (const Json& meaning : meaning_arr) {
			// Get thesaurus entries
			const Json thesaurus_entries = meaning["definitions"];

			// For each thesaurus entry
			const Json::array& thesaurus_entry_arr =
				thesaurus_entries.array_items();
			for (const Json& thesaurus_entry : thesaurus_entry_arr) {
				// Get definition
				const std::string definition =
					thesaurus_entry["definition"].string_value();
				
				if (!definition.empty()) {
					// If definition is not empty, return it.
					return definition;
				}

				// Otherwise, keep looking for a non-empty definition.
			}

		}
	}

	// Failed to find definition in response. Return empty string.
	return "";
}

/*
 * Function: query_definition
 * Description: Queries the definition of a given word and returns it
 * 		if the word exists in the dictionaryapi.dev database. Else, it returns
 * 		an empty string.
 * Parameters:
 * 		word (std::string): Word for which to query definition
 * Returns (string): Definition of word if found, or empty string otherwise.
 */
std::string query_definition(std::string word) {
	// Construct http client
	httplib::Client cli(DICTIONARY_API_HOST);

	// Make request
	auto res = cli.Get(build_request_endpoint(word));

	if (res->status != 200) {
		// If status is not 200 (OK), then the word does not exist in the
		// dictionary API's database. Return empty string for definition
		return "";
	}

	// Parse body to Json (array of words)
	std::string err;
	const Json words = Json::parse(res->body, err);
	if (!err.empty()) {
		// If an error occurred in parsing, return an empty string for
		// definition.
		return "";
	}

	// Extract definition
	std::string definition = extract_definition(words);

	return definition;
}

/*
 * Function: extract_audio_url
 * Description: Extracts the first dictionaryapi.dev phonetic audio sample URL
 * 		available from the JSON response.
 * Parameters:
 * 		words (json11:Json): Parsed json11::Json object of response from
 * 			dictionaryapi.dev
 * Returns (std::string): Audio sample URL. If none are available, returns
 * 		an empty string.
 */
std::string extract_audio_url(const Json words) {
	// For each word
	const Json::array& word_arr = words.array_items();
	for (const Json& word : word_arr) {
		// Get phonetics
		const Json phonetics = word["phonetics"];

		// For each phonetic entry
		const Json::array& phonetic_arr = phonetics.array_items();
		for (const Json& phonetic : phonetic_arr) {
			// Get audio url
			const std::string audio_url = phonetic["audio"].string_value();

			if (!audio_url.empty()) {
				// If audio_url is not empty, return it.
				return audio_url;
			}

			// Otherwise, keep looking for a non-empty URL.
		}
	}

	// Failed to find audio URL in response. Return empty string.
	return "";
}

/*
 * Function: query_audio_url
 * Description: Queries the dictionaryapi.dev phonetic audio sample URL of a
 * 		given word and returns it if the word exists in the dictionaryapi.dev
 * 		database. Else, it returns an empty string.
 * Parameters:
 * 		word (std::string): Word for which to query audio sample URL
 * Returns (string): Audio sample URL of word if found. If the word is not found
 * 		in the database or the word doesn't have an audio sample URL associated
 * 		with it, this function returns an empty string.
 */
std::string query_audio_url(std::string word) {
	// Construct http client
	httplib::Client cli(DICTIONARY_API_HOST);

	// Make request
	auto res = cli.Get(build_request_endpoint(word));

	if (res->status != 200) {
		// If status is not 200 (OK), then the word does not exist in the
		// dictionary API's database. Return empty string for definition
		return "";
	}

	// Parse body to Json (array of words)
	std::string err;
	const Json words = Json::parse(res->body, err);
	if (!err.empty()) {
		// If an error occurred in parsing, return an empty string for
		// definition.
		return "";
	}

	// Extract audio URL
	std::string audio_url = extract_audio_url(words);

	return audio_url;
}

/*
 * Function: extract_pronunciation
 * Description: Extracts the first available formal pronunciation from the
 * 		dictionaryapi.dev JSON response.
 * Parameters:
 * 		words (json11:Json): Parsed json11::Json object of response from
 * 			dictionaryapi.dev
 * Returns (std::string): First available pronunciation in JSON response. If
 * 		none are available, returns an empty string.
 */
std::string extract_pronunciation(const Json words) {
	// For each word
	const Json::array& word_arr = words.array_items();
	for (const Json& word : word_arr) {
		// Get pronunciation
		const std::string pronunciation = word["phonetic"].string_value();

		if (!pronunciation.empty()) {
			// If pronunciation is not empty, return it
			return pronunciation;
		}

		// Otherwise, check the ["phonetics"]["text"] fields

		// Get phonetics
		const Json phonetics = word["phonetics"];

		// For each phonetic entry
		const Json::array& phonetic_arr = phonetics.array_items();
		for (const Json& phonetic : phonetic_arr) {
			// Get text of phonetic
			const std::string pronunciation = phonetic["text"].string_value();

			if (!pronunciation.empty()) {
				// If pronunciation is not empty, return it.
				return pronunciation;
			}

			// Otherwise, keep looking for a non-empty pronunciation
		}
	}

	// Failed to find pronunciation in response. Return empty string.
	return "";
}

/*
 * Function: query_pronunciation
 * Description: Queries the dictionaryapi.dev formal pronunciation text of a
 * 		given word and returns it if the word exists in the dictionaryapi.dev
 * 		database. Else, it returns an empty string.
 * Parameters:
 * 		word (std::string): Word for which to query pronunciation
 * Returns (string): Pronunciation of word if found. Else, returns an empty
 * 		string.
 */
std::string query_pronunciation(std::string word) {
	// Construct http client
	httplib::Client cli(DICTIONARY_API_HOST);

	// Make request
	auto res = cli.Get(build_request_endpoint(word));

	if (res->status != 200) {
		// If status is not 200 (OK), then the word does not exist in the
		// dictionary API's database. Return empty string for definition
		return "";
	}

	// Parse body to Json (array of words)
	std::string err;
	const Json words = Json::parse(res->body, err);
	if (!err.empty()) {
		// If an error occurred in parsing, return an empty string for
		// definition.
		return "";
	}

	// Extract pronunciation
	std::string pronunciation = extract_pronunciation(words);

	return pronunciation;
}


/* END OF TEMPLATE CODE */

// TODO Your code goes below this comment.

/*
 * Function: extract_example
 * Description: Extracts the first example sentence available in the given
 *              JSON response from dictionaryapi.dev.
 * Parameters:
 *              words (json11:Json): Parsed json11::Json object of response from
 *                      dictionaryapi.dev
 * Returns (std::string): First example sentence available in given JSON
 *                        response.
 *              If none are available, returns an empty string.
 */
std::string extract_example(const Json words) {
        // For each word
        const Json::array& word_arr = words.array_items();
        for (const Json& word : word_arr) {
                // Get meanings
                const Json& meanings = word["meanings"];

                // For each meaning
                const Json::array& meaning_arr = meanings.array_items();
                for (const Json& meaning : meaning_arr) {
                        // Get thesaurus entries
                        const Json thesaurus_entries = meaning["definitions"];

                        // For each thesaurus entry
                        const Json::array& thesaurus_entry_arr =
                                thesaurus_entries.array_items();
                        for (const Json& thesaurus_entry : thesaurus_entry_arr) {
                                // Get example sentence
                                const std::string example =
                                        thesaurus_entry["example"].string_value();

                                if (!example.empty()) {
                                        // If example is not empty, return it.
                                        return example;
                                }

                                // Otherwise, keep looking for a non-empty
                                // example sentence.
                        }

                }
        }

        // Failed to find example sentence in response. Return empty string.
        return "";
}

/*
 * Function: query_example
 * Description: Queries an example sentence of a given word and returns it
 *              if the word exists in the dictionaryapi.dev database. Else,
 *              it returns an empty string.
 * Parameters:
 *              word (std::string): Word for which to query an example sentence
 * Returns (string): Example sentence of word if found, or empty string
 *                   otherwise.
 */
std::string query_example(std::string word) {
        // Construct http client
        httplib::Client cli(DICTIONARY_API_HOST);

        // Make request
        auto res = cli.Get(build_request_endpoint(word));

        if (res->status != 200) {
                // If status is not 200 (OK), then the word does not exist in the
                // dictionary API's database. Return empty string for definition
                return "";
        }

        // Parse body to Json (array of words)
        std::string err;
        const Json words = Json::parse(res->body, err);
        if (!err.empty()) {
                // If an error occurred in parsing, return an empty string for
                // example sentence
                return "";
        }

        // Extract example sentence
        std::string example = extract_example(words);

        return example;
}

/* Function: error_handling
 * Description: Takes the users input of what information they want about their
 * 		word, then determines if it's valid or invalid. If it's invalid
 * 		the function returns false, if it's valid it returns true
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *			 want about their word    
 * Returns:
 * 	false (boolean): If users input is invalid
 * 	true (boolean): If users input is valid
*/
bool error_handling(std::string choice){
	if (choice != "a" && choice != "b" && choice != "c" && choice != "d" 
			&& choice != "e"){
		return false;
	} else {
		return true;
	}
}

/* Function: user_word_input
 * Description: Prompts the user for a single word then stores that word in a
 * 		string variable 
 * Returns (string): The word the user input
*/
std::string user_word_input(){
	std::cout << "Please enter a single word" << std::endl;
	std::string given_word;
	std::getline(std::cin, given_word);
	return given_word;
}

/* Function: options
 * Description: Declares two variables, choice (string), and easier_on_computer
 * 		(boolean). In a do-while loop it prompts the user to choose 1 
 * 		of 5 options and stores that choice within the choice variable.
 * 		It then takes the easier_on_computer function and sets it equal
 * 		to the error_handling function and calls the function at the
 * 		same time. It then determines that function returned true or
 * 		false, then prints out on a message informing the user of the
 * 		invalid option.
 * Returns (string): The choice the user makes about what type of information
 * 		     the user would like about their word
*/
std::string options(){
	std::string choice;
	
	// This takes the error handling function and stores it in a boolean
	// so it doesn't run twice in this function
	bool easier_on_computer;
	do {
		std::cout << "Please choose one of the following options by "
		       "entering the letter that corresponds to the one you "
		       		"want" << std::endl;
		std::cout << "(a) Lookup the definition of a given word" 
			<< std::endl;
		std::cout << "(b) Lookup a URL to an audio sample of a given " 
			"word being spoken" << std::endl;
		std::cout << "(c) Lookup the formal pronunciation of a" 
			" given word" << std::endl;
		std::cout << "(d) Lookup an example sentence of a given word" 
			<< std::endl;
		std::cout << "(e) Exit program" << std::endl;
		std::getline (std::cin, choice);
		easier_on_computer = error_handling(choice);
		if (easier_on_computer == false) {
			std::cout << "That is not a valid option" << std::endl;
		}
	} while (easier_on_computer == false);
	return choice;
}

/* Function: valid_input
 * Description: Declare a string varliable called input. In an if statemant
 * 		with the conditions being if the user's choice is valid, it
 * 		initializes the input variable to the user_word_input and 
 * 		runs it
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *                       want about their word
 * Returns (string): input variable
 */
std::string valid_input (std::string choice){
	std::string input;
	if (choice == "a" || choice == "b" || choice == "c" || choice == "d"){
		input = user_word_input();
	}
	return input;
}

/* Function: retrieving_definition
 * Description: Within an if statement with the condition being the user wants
 * 		the definition of their word, it declares and initializes a
 * 		variable to the query_definition function. In the nested if
 * 		statement it checks if the definition function returns an 
 * 		empty set and prints out a message informing the user that 
 * 		the API doesn't have the definition if it is. If it's not,
 * 		it prints out the definition of the word 
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *                       want about their word
 *      input (string): The word that the user gave 
 */
void retrieving_definition(std::string input,std::string choice){
	if (choice == "a"){
		std::string definition_of_word = query_definition(input);
		if (definition_of_word == ""){
			std::cout << "Sorry, the API doesn't contain the "
				"definition of that word" << std::endl;
		} else{
			std::cout << "The definition of your word is: " 
				<< definition_of_word << std::endl;
		}
	}
}

/* Function: retrieving_URL_of_audio_sample
 * Description: Within an if statement with the condition being the user wants
 *              the URL of an audio sample of their word, it declares and 
 *              initializes a variable to the query_audio_url function. 
 *              In the nested if statement it checks if the URL function 
 *              returns an empty set and prints out a message informing 
 *              the user that the API doesn't have an audio sample if it is. 
 *              If it's not, it prints out the URL of the audio sample
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *                       want about their word
 *      input (string): The word that the user gave
 */
void retrieving_URL_of_audio_sample(std::string input,std::string choice){
        if (choice == "b"){
        	std::string URL_of_audio_sample = query_audio_url(input);
        	if (URL_of_audio_sample == ""){
			std::cout << "Sorry, the API doesn't contain a URL "
				"for an audio sample of that word" 
					<< std::endl;
		} else {	
			std::cout << "Here is a URL for an audio sample of "
				"your word: " << URL_of_audio_sample 
					<< std::endl;
		}
	}
}

/* Function: retrieving_pronunciation
 * Description: Within an if statement with the condition being the user wants
 *              the formal pronunciation of their word, it declares and
 *              initializes a variable to the query_pronunciation function.
 *              In the nested if statement it checks if the pronunciation 
 *              function returns an empty set and prints out a message 
 *              informing the user that the API doesn't have the pronunciation 
 *              if it is. If it's not, it prints out the pronunciation of 
 *              the word
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *                       want about their word
 *      input (string): The word that the user gave
 */
void retrieving_pronunciation(std::string input,std::string choice){
        if (choice == "c"){
                std::string pronunciation_of_word = query_pronunciation(input);
                if (pronunciation_of_word == ""){
			std::cout << "Sorry, the API doesn't contain a formal "
				"pronunciation of your word" << std::endl;
		} else {
			std::cout << "The formal pronunciation of your word " 
				"is: " << pronunciation_of_word << std::endl;
        	}
	}
}

/* Function: retrieving_example
 * Description: Within an if statement with the condition being the user wants
 *              an example sentence of their word, it declares and
 *              initializes a variable to the query_example function.
 *              In the nested if statement it checks if the example sentence
 *              function returns an empty set and prints out a message
 *              informing the user that the API doesn't have an example
 *              if it is. If it's not, it prints out an example sentence of
 *              the word
 * Parameters:
 *      choice (string): The choice the user makes for what information they
 *                       want about their word
 *      input (string): The word that the user gave
 */
void retrieving_example(std::string input,std::string choice){
        if (choice == "d"){
                std::string example_of_word = query_example(input);
                if (example_of_word == ""){
                        std::cout << "Sorry, the API doesn't contain an"
                                " example sentence of your word" << std::endl;
                } else {
                        std::cout << "An example sentence of your word "
                                "is: " << example_of_word << std::endl;
                }
        }
}

int main() {
	// Commented below are examples of how to use the provided template
	// functions to get definitions, audio URLs, and pronunciation of a given
	// word string. Uncomment them to try them out. Note that not all words have
	// definitions, audio URLs, or pronunciations available through the free
	// API that the template code uses. In such a case, the returned string will
	// be empty (i.e., blank). Your program should handle this as described
	// in the assignment document.
	
	// Definition example:
	// std::string definition = query_definition("what");
	// std::cout << "Definition of 'what': " << definition << std::endl;

	// Audio sample URL example:
	// std::string audio_url = query_audio_url("hello");
	// std::cout << "Audio URL for 'hello': " << audio_url << std::endl;

	// Pronunciation example:
	// std::string pronunciation = query_pronunciation("mischievous");
	// std::cout << "Pronunciation of 'mischievous': "
	// 	<< pronunciation << std::endl;

	// TODO Your program starts here. Of course, you should write other
	// functions as well.
	
	// Declares a string function to then be initialized to the options 
	// function
	std::string choice;
	
	// A do-while loop with the condition being the user inputs anything
	// other than "e" which ends the program
	do{
		// Initializes the choice variavle to the options function
		// and calls it
		choice = options();
		
		// Declares and initializes a string function to the
		// valid_input function with the argument being the type
		// of information the user wants about their word
		std::string input = valid_input(choice);
		
		// Calls the function that gives the user the definition
		// of their word
		retrieving_definition(input,choice);

		// Calls the function that gives the user the URL of an
		// audio sample of their word	
		retrieving_URL_of_audio_sample(input,choice);
		
		// Calls the function the gives the formal pronunciation
		// of their word		
		retrieving_pronunciation(input,choice);
		
		// Calls the function that gives an example sentence of
                // their word
		retrieving_example(input,choice);
	} while (choice != "e");
}
