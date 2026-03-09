// TODO Complete the assignment following the instructions in the assignment
// document. Refer to the Concurrency lecture notes in Canvas for examples.
// You may also find slides 50 and 51 from Ben Brewster's Concurrency slide
// deck to be helpful (you can find Brewster's slide decks in Canvas -> files).

#include <stdio.h>
#include <pthread.h>

struct thread_stuff{
    pthread_mutex_t* my_mutex_pointer;
    pthread_cond_t* my_cond_1_pointer;
    pthread_cond_t* my_cond_2_pointer;
    int* my_count_pointer;
    int* updated_count;
    int* printed;
};

void start_prog(){
    printf("PROGRAM START\n");
}

void* thread_2_function(void* args){
    struct thread_stuff* thread_args = (struct thread_stuff*) args;
    int old_count = 0;


    while(old_count != 10){
        pthread_mutex_lock(thread_args->my_mutex_pointer);
        printf("CONSUMER: MUTEX LOCKED\n");

        while(!*(thread_args->updated_count)){
            printf("CONSUMER: WAITING ON CONDITION VARIABLE 1\n");
            pthread_cond_wait(thread_args->my_cond_1_pointer, thread_args->my_mutex_pointer);
        }

        printf("Count update %d -> %d\n", old_count, *(thread_args->my_count_pointer));
        
        printf("CONSUMER: SIGNALING CONDITION VARIABLE 2\n");
        pthread_cond_signal(thread_args->my_cond_2_pointer);
        *(thread_args->printed) = 1;
        *(thread_args->updated_count) = 0;
        printf("CONSUMER: MUTEX UNLOCKED\n");
        pthread_mutex_unlock(thread_args->my_mutex_pointer);

        old_count += 1;
    }
    return NULL;
}

int main() {
    int my_count = 0;
    pthread_t thread2 = {0};
    void* return_val;
    pthread_mutex_t my_mutex;   
    pthread_cond_t my_cond_1;
    pthread_cond_t my_cond_2;
    struct thread_stuff args;
    int update = 0;
    int printed = 0;

    pthread_mutex_init(&my_mutex, NULL);
    pthread_cond_init(&my_cond_1, NULL);
    pthread_cond_init(&my_cond_2, NULL);

    args.my_mutex_pointer = &my_mutex;
    args.my_cond_1_pointer = &my_cond_1;
    args.my_cond_2_pointer = &my_cond_2;
    args.my_count_pointer = &my_count;
    args.updated_count = &update;
    args.printed = &printed;

    start_prog();

    pthread_create(&thread2, NULL, thread_2_function, &args);
    printf("CONSUMER THREAD CREATED\n");
    
    int i = 0;
    while(i != 10){
        printed = 0;
        pthread_mutex_lock(&my_mutex);
        printf("PRODUCER: MUTEX LOCKED\n");
        my_count += 1;
        
        printf("PRODUCER: SIGNALING CONDITION VARIABLE 1\n");
        pthread_cond_signal(&my_cond_1);
        update = 1;

        while(printed == 0){
            printf("PRODUCER: WAITING ON CONDITION VARIABLE 2\n");
            pthread_cond_wait(&my_cond_2, &my_mutex);
        }

        printf("PRODUCER: MUTEX UNLOCKED\n");
        pthread_mutex_unlock(&my_mutex);
        i++;
    }

    printf("PROGRAM END\n");
}
