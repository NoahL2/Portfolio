#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

struct command_line{
	char* command;	// First word in users input i.e. "cd" "status" "pwd"
	char* input_line[512]; // Stores the tokens of the user's input
	char* arguments[512]; // The arguments following the command, before the "<" or ">"
	char* input; // Name of the file if user enters input redirection
	char* output; // Name of the file if user enters output redirection
	int background; // Int keeping track of if user enters "&". 1 if they do, 0 otherwise
};

/*
 * A global variable that a signal handler can use that
 * is changed to 1 if the program is in foreground
 * only mode
 */
volatile sig_atomic_t foreground = 0;
void SIGTSTP_handler(int sig){
	if (foreground == 0){
		char* mesg = "\nEntering foreground-only mode (& is now ignored)\n";

		/*
		 * Here I used the write function instead of printf because write() is
		 * a reentrant function. It doesn't corrupt the program's state if it 
		 * gets interupted
		 */
		write(STDOUT_FILENO, mesg, 50);
		foreground = 1;
	} else {
		char* mesg = "\nExiting foreground-only mode\n";
		write(STDOUT_FILENO, mesg, 30);
		foreground = 0;
	}
}

struct command_line tokenizing(char* user_input){
	struct command_line cl = {0};
	int num_of_chars = 0;
	int index_of_sign = 0;
	int index_of_sign2 = 0;
	char* token;
	int num_of_args = 0;
	int i = 0;

	/*
	 * Tokenizes the user's input into the the input_line array
	 */
	token = strtok(user_input, " ");
	while (token != NULL){
		cl.input_line[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	cl.command = cl.input_line[0]; // Stores first token in command
	for(int j = 1; j < i; j++){

		/*
		 * If the user enters an input redirections, stores the next index of the
		 * input array (the file name) in the input variable
		 */
		if (strcmp(cl.input_line[j],"<") == 0){
			cl.input = cl.input_line[j+1];
			j++;
			continue;
		}

		/*
		 * If the user enters an output redirections, stores the next index of the
		 * input array (the file name) in the output variable
		 */
		if (strcmp(cl.input_line[j], ">") == 0){
			cl.output = cl.input_line[j+1];
			j++;
			continue;
		}

		/*
		 * if the user chooses for the process to be a background one,
		 * the background variable gets switched to 1
		 */
		if (strcmp(cl.input_line[j], "&") == 0){
			cl.background = 1;
			continue;
		}

		/*
		 * stores the provided arguments into the arguments array
		 */
		cl.arguments[num_of_args] = cl.input_line[j];
		num_of_args++;
	}
	cl.arguments[num_of_args] = NULL; // Last index of arguments array is NULL
	return cl;
}

void changing_dir(struct command_line cl){
	char* val = getenv("HOME"); // Gets the value of the HOME environment variable 
	if (cl.arguments[0] == NULL){
		// If the user doesn't specify a directory, the working directory becomes the value (the path) of the HOME variable
		chdir(val); 
	} else {
		// If they do specify a directory, the working directory changes to that directory if it exists
		chdir(cl.arguments[0]);
	}
}

// background[] is an array that stores the pids of the background processes
// num is the number of background pids
int kill_process(pid_t background[], int num){
	if (num == 0){ 
		return 1; // If there are no background processes return immediately
	} else {
		for (int i = 0; i < num; i++){
			if (background[i] > 0){
				// If there are background processes, loops through all of them and sends a kill signal to each one
				kill(background[i], SIGKILL);  
			}
		}
		return 1;
	}
}

void status_display(int exit_status){
	int status = 0;
	if (WIFEXITED(exit_status)){ 			// checking to see of the process terminated normally
		status = WEXITSTATUS(exit_status);	// If it did, this gets the exit code and prints it out 
		printf("exit value %d\n", status);
	} else if (WIFSIGNALED(exit_status)){	// Checks to see if the process was terminated by a signal
		status = WTERMSIG(exit_status);		// If it did, this gets the signal number used to terminate the process
		printf("Terminated by signal %d\n", status); // Prints out the signal number
	}
}

int main() {
	// See the pseudocode in Canvas to get an idea of where to start
	char user_input[100000]; // First array used to store the user input 
	char processed_input[100000]; // Second array for user input with "$$" swapped for pid
	int status; // Variable to store status code from waitpid calls
	int other_status = 0; // Variable used to store status of child process when parent is waiting for it to terminate
	pid_t fork_result; // Result of fork function call
	pid_t background_pid[100];	// Array for storing the pids of the background processes
	pid_t wait_results;	// The result of the waitpid function call
	pid_t get_parent_pid; // Stores pid of parent process
	int pid_counter = 0; // The number of background pids
	struct command_line command;
	struct sigaction sigint_signal = {0};
	struct sigaction sigstop_signal = {0};
	int new_index;	// used to match indices of processed_input and user_input
	char* exec_command[50]; // Array of strings for execvp

    sigint_signal.sa_handler = SIG_IGN; // sets the handler for ctrl+c to ignore
	sigfillset(&sigint_signal.sa_mask); // This blocks all the signals while it's running
    sigint_signal.sa_flags = SA_RESTART; // Restarts the stuff that was interuppted by the handler


    sigstop_signal.sa_handler = SIGTSTP_handler; // Sets the handler for ctrl+z to point to the SIGTSTP_handler function
    sigfillset(&sigstop_signal.sa_mask);
    sigstop_signal.sa_flags = SA_RESTART; // Restarts the stuff that was interuppted by the handler

	// Gets the pid of the parent process, this won't change while the program is running but will if program is restarted
	get_parent_pid = getpid();  
	char string[100];
	sprintf(string, "%d", get_parent_pid); // Changes pids to strings and stores them

	sigaction(SIGINT, &sigint_signal, NULL); // If the user presses ctrl+c this catches it and ignores it

	/*
	 * If the user presses ctrl+z this catches it and enters forground only mode. If they press it again it 
	 * exits that mode
	 */
	sigaction(SIGTSTP,&sigstop_signal, NULL); 

	while(1){
		for (int i = 0; i < pid_counter; i++){ 

			/*
			 * This waitpid call is only checking if all background processes have finished.
			 * Here the parent process doesn't have to wait for the child processes to terminate.
			 * The WNOHANG argument is what instructs the parent process not to wait
			 */ 
			wait_results = waitpid(background_pid[i], &status, WNOHANG); 
			if (wait_results > 0){
				printf("background pid %d is done: ", background_pid[i]); 
				status_display(status);
				fflush(stdout);

				/*
				 * Once a background process terminates, this removes that pid from the pid array and
				 * shrinks its size
				 */ 
				background_pid[i] = background_pid[pid_counter-1];
				pid_counter--;
				i--; 
			} 
		}

		printf(": ");
		fflush(stdout);
		fgets(user_input, 100000, stdin);
		user_input[strlen(user_input) - 1] = '\0';

		new_index = 0;
		processed_input[0] = '\0'; // Initialize array to a null terminator

		/*
		 * This loop moves everything from the initial user input array into a second
		 * one so that when the user enters "$$" they get replaced with the pid and when
		 * they enter "#" it gets ignored
		 */
		for (int i = 0; i < strlen(user_input); i++){
			if (user_input[i] == '$' && user_input[i+1] == '$'){  // Checks if one "$" is directly followed by another
				// Copies the parent pid into the new array at the starting at the first "$" index
				strcpy(processed_input + new_index, string); 
				new_index += strlen(string);
				i++;
				continue;
			}
			if (user_input[i] == '#'){
				break;	// If the user enters "#" than the for loop ends and processed_input stays as a null terminator
			}
			processed_input[new_index] = user_input[i]; // Moves the rest of the user_input into new array after the pid
			new_index++;
		}
		processed_input[new_index] = '\0';

		if (processed_input[0] == '\0'){
			// If processed_input is still empty (if the user enters "#") then it skips this iteration of the while loop
			continue; 
		}

		command = tokenizing(processed_input); // Tokenizes the array with "$$" swapped for the pid

		int index = 0;
		int y = 0;
		// Forgot execvp() needed an array of strings so I created and filled on here
		exec_command[index] = command.command;
		index = 1; 
		while(command.arguments[y] != NULL){
			exec_command[index] = command.arguments[y];
			index++;
			y++;
		}
		exec_command[index] = NULL;

		if (strcmp(command.command, "cd") == 0){
			changing_dir(command);	// If the user enters "cd" the changing directory function is called
			continue;	// The rest of this loop iteration is skipped
		} else if (strcmp(command.command, "exit") == 0){
			int terminate = kill_process(background_pid, pid_counter); // Kills all background processes
			if (terminate == 1){
				return 0;	// kill_process will always return 1. This terminates the program
			}
		} else if (strcmp(command.command, "status") == 0){
			status_display(other_status);	// Displays the status of the parent process
			continue;
		} else {

			/*
			 * If the user doesn't enter any of the built-in commands then the program forks. A child
			 * process is created and it's pid is stored in fork_result
			 */
			fork_result = fork();	
			if (fork_result == 0){ // This is only true in the child process

				if(command.background == 0){	// If this isn't a background process
					sigstop_signal.sa_handler = SIG_IGN; // Sets the handler for ctrl+z to ignore
					sigaction(SIGTSTP,&sigstop_signal, NULL); // If the user presses ctrl+z this catches it and ignores it
					sigint_signal.sa_handler = SIG_DFL; // Sets the handler for ctrl+c to its default behavior
					sigaction(SIGINT, &sigint_signal, NULL);  // If the user presses ctrl+c this catches it and handles it
					
					if (command.input != NULL){

						/*
						 * Opens an input redirection file that can only be read.
						 * Stores the file descriptor in input_name
						 */
						int input_name = open(command.input, O_RDONLY);
						// This function redirects the standard in to the file with the file descriptor stored in input_name

						/*
						 * The open function returns and -1 if there was an error opening the file. Since
						 * this open function call doesn't create a file if it doesn't exist, then if the 
						 * user supplys a non-existing file name an error message will print out and the 
						 * exit function call ends the process with status code 1
						 */
						if (input_name == -1){
							printf("%s: this file or directory does not exist\n", command.input);
							exit(1);
						}
						dup2(input_name, STDIN_FILENO); 
						close(input_name);
					}
					if (command.output != NULL){

						/*
						 * Opens and/or creates  an output redirection file that can only be written to.
						 * If there is already something in that file, it gets replaced.
						 * Stores the file descriptor in output_name
						 */
						int output_name = open(command.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						// This function redirects the standard out to the file with the file descriptor stored in output_name
						dup2(output_name, STDOUT_FILENO);
						close(output_name);
					}
				} else if (command.background == 1){
					sigaction(SIGINT, &sigint_signal, NULL);
					if(command.input == NULL){
						// If the user doesn't supplay a file name and it is a child process, this reads from "/dev/null"
						int no_input = open("/dev/null", O_RDONLY);
						dup2(no_input, STDIN_FILENO);
						close(no_input);
					}
					if(command.output == NULL){
						// If the user doesn't supplay a file name and it is a child process, this writes to  "/dev/null"
						int no_output = open("/dev/null", O_WRONLY);
						dup2(no_output, STDOUT_FILENO);
						close(no_output);
					}
				}

				/*
				 * This execvp allows the child process to run a different program from the parent. 
				 * It does this so that the non-built in commands can be run without restarting the parent function
				 */
				execvp(exec_command[0], exec_command);
				perror("execvp");
				exit(1);
			} else {
				if(command.background == 1 && foreground == 0){
					printf("Background pid is %d\n", fork_result);
					fflush(stdout);
					background_pid[pid_counter] = fork_result;
					pid_counter++;
				} else {
					int p_status;

					// Parent process has to wait for the child process to terminate before it can continue
					waitpid(fork_result, &p_status, 0);
					other_status = p_status; 
				}
			}
		}
	}
}
