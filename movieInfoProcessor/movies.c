// Complete this file to write a C program that adheres to the assignment
// specification. Refer to the assignment document in Canvas for the
// requirements. Refer to the example-directory/ contents for some example
// code to get you started.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie {
	char* title;
	char* year;
	char* lang[5];
	char* rating;
	int lang_count;
};

struct list {
    struct movie m;
    struct list* next;
};

struct list* init_list (){
    struct list* new_node = (struct list*) malloc(sizeof(struct list));
    new_node->next = NULL;
    return new_node;
}

void free_movies(struct movie* m, int num_of_movs){
    int i,j;

    for (i = 0; i < num_of_movs; i++){
        free(m[i].title);
        m[i].title = NULL;
        free(m[i].year);
         m[i].year = NULL;
        free(m[i].rating);
         m[i].rating = NULL;
        for (j = 0; j < m[i].lang_count; j++){
            if (m[i].lang[j]){
                free(m[i].lang[j]);
                 m[i].lang[j] = NULL;
            }
        }
    }
    free(m);
}

void free_list(struct list* node){
    struct list* current = node;
    struct list* next;

    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

struct movie file_reading(FILE* file){
    char* text_line = NULL;
    size_t buffer_size = 0;
    ssize_t line_size = getline(&text_line, &buffer_size, file);
    struct movie m;

    if(line_size > 0){
        text_line[line_size - 1] = '\0';
        line_size--;
        char* title = strtok(text_line, ",");
        char* year = strtok(NULL, ",");
        char* lang = strtok(NULL, ",");
        char* rating = strtok(NULL, ",");

        // Gets rid of square brackets surrounding the languages
        if (lang[0] == '['){
            lang++;
        }
        char* end = strchr(lang, ']');
        if (end) {
            *end = '\0';
        }
        char* lang1 = strtok(lang, ";");

        m.title = (char*) malloc(sizeof(char) * (strlen(title) + 1));
        strcpy(m.title, title);
        m.year = (char*) malloc(sizeof(char) * (strlen(year) + 1));
        strcpy(m.year, year);
        
        // Tokenizes individual langauges and stores them in a language array
        int i = 0;
        while (lang1 != NULL && i < 5){
            m.lang[i] = (char*) malloc(sizeof(char) * (strlen(lang1) + 1));
            strcpy(m.lang[i], lang1);
            lang1 = strtok(NULL, ";");
            i++;
        }

        m.rating = (char*) malloc(sizeof(char) * (strlen(rating) + 1));
        strcpy(m.rating, rating);

        m.lang_count = i;
    } else {
        m.title = NULL;
        m.year = NULL;
        int i;
        for (i = 0; i < 5; i++){
            m.lang[i] = NULL;
        }
        m.rating = NULL;
    }
    
    free(text_line);

    return m;
};

void movies_in_year(struct movie* m, int num_of_movs){
    char user_input[10];
    int year;
    int year_count = 0;
    printf("Please enter desired year: ");
    fgets(user_input,10,stdin);
    user_input[strlen(user_input) - 1] = '\0';
    year = atoi(user_input);
    int i;
    for (i = 0; i < num_of_movs; i++){
        if (atoi(m[i].year) == year){
            printf("%s %s\n", m[i].title, m[i].rating);
            year_count++;
        } 
    } 
    
    if (year_count == 0){
        printf("No movies from that year\n");
    }
}

// Compares current year to years that already had their highest rating found
int past_year_check(int* past_years, int current_year, int movie_num){
    int i;
    for (i = 0; i < movie_num; i++){
        if (past_years[i] == current_year){
            return 0;
        }
    }
    return 1;
}

// This function prints out the highest rated movie for each year
void highest_rated_movie(struct movie* m, int num_of_movs){
    int i,j;
    int current_year;
    double current_rating;
    int past_years[num_of_movs];
    int years_count = 0;
    double best_rating;
    int best_index;
    for (i = 0; i < num_of_movs; i++){
        current_year = atoi(m[i].year);
        current_rating = strtod(m[i].rating, NULL);

        // Makes sure the highest rating for the year hasn't already been found
        // If it has then it skips the current iteration
        if (!past_year_check(past_years, current_year, years_count)){ 
            continue;
        }
        past_years[years_count++] = current_year;
        best_rating = current_rating;
        best_index = i;

        for (j = i+1; j < num_of_movs; j++){
            if(atoi(m[j].year) == current_year){

                // Changes the rating from a string to a decimal
                current_rating = strtod(m[j].rating, NULL);
                if(best_rating < current_rating){
                    best_rating = current_rating;
                    best_index = j;
                }
            }
        }
        printf("%s %.1f %s\n", m[best_index].year, best_rating, m[best_index].title);
    }
}

void movies_in_lang(struct movie* m, int num_of_movs, struct list* head){
    int i,j;
    struct list* current = head;
    char user_input[100];
    int lang = 0;
    printf("Please enter desired language: ");
    fgets(user_input,100,stdin);
    user_input[strlen(user_input) - 1] = '\0';
    for (i = 0; i < num_of_movs; i++){
        for (j = 0; j < m[i].lang_count; j++){
            
            // Compares the user's desired language and each language of the current year
            // If it's the same it prints out the information of that movie
            if (strcmp(m[i].lang[j], user_input) == 0) {
                printf("%s %s %s\n", m[i].year, m[i].rating, m[i].title);
                lang++;
                break;
            }
        }   
    }
    if (lang == 0){
        printf("No info about movies in %s\n", user_input);
    }
}

int ask_question(){
	char user_input[100];
	printf("\nPlease enter number for option you would like to choose\n");
	printf("1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year\n");
	printf("3. Show the title and year of release of all movies in a specific language\n");
	printf("4. Exit Program\n");
    printf("Your desired choice: ");
	fgets(user_input, 100, stdin);
	user_input[strlen(user_input) - 1] = '\0';
	
	if (user_input[0] == '1'){
        return 1;
	} else if (user_input[0] == '2'){
        return 2;
	} else if (user_input[0] == '3'){
         return 3;
	} else if (user_input[0] == '4'){
    	printf("Terminating program\n");
        return 4;
	}
    return 0;
}

struct list* populate_list( struct movie* movie,  int num_of_movs){
    int i;
    struct list* head = init_list();
    struct list* current = head;

    head->m = movie[0];

    if (num_of_movs <= 0){
        return NULL;
    }

    // Puts each movie and all the information associated with that movie
    // into a single node of the linked list
    for (i = 1; i < num_of_movs; i++){
        current->next = init_list();
        current = current->next;
        current->m = movie[i];
    }

    return head;
}

int main(int argc, char* argv[]){
	int users_int;
    struct list* head; 
    struct movie* movies = NULL;
    int movie_number = 0;
    FILE* file = fopen(argv[1],"r");
    if (!file){
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    // Gets rid of the first line
    char* first_line = NULL;
    size_t size_of_buffer;
    getline(&first_line, &size_of_buffer, file);
    free(first_line);


    while (!feof(file)){
        struct movie m = file_reading(file);
        if (m.title){
            movie_number++;
            movies = realloc(movies, sizeof(struct movie) * movie_number);
            movies[movie_number - 1] = m;
        }
    }
	
    head = populate_list(movies, movie_number);
    do {
        users_int = ask_question();
        if (users_int == 1){
            movies_in_year(movies, movie_number);
        } else if (users_int == 2){
            highest_rated_movie(movies, movie_number);
        } else if (users_int == 3){
            movies_in_lang(movies, movie_number, head);
        }
    } while (users_int != 4);
    
    free_movies(movies, movie_number);
    movies = NULL;
    free_list(head);
	fclose(file);
    return 0;
}

