#include <pthread.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define NUM_THREADS 5

// Structure that will be used to pass arguments
// to each thread
typedef struct {
    int num;
    int lower_bound;
    int upper_bound;
} thread_args;

// Data that is shared by all threads
int results[NUM_THREADS];
pthread_t threadids[NUM_THREADS];

void *runner(void *param); // Threads execute this function

int main(int argc, char *argv[])
{
    pthread_attr_t attr; // Thread attributes

    // set the default attributes of the thread
    pthread_attr_init(&attr);

    int count = atoi(argv[1]); // Number of integers to add up
    
    
    int range = count / NUM_THREADS; // Number of integers to be summed by each thread
                                     // What if count < NUM_THREADS?
                                     // What if it doesn't divide evenly?
    
    int next_lower_bound = 1; // Starting point for the next thread

    for (int i = 0; i < NUM_THREADS; ++i) {

        // Set up the argument for this thread
        thread_args *arg = new thread_args;
        arg->num = i;
        arg->lower_bound = next_lower_bound;
        arg->upper_bound = arg->lower_bound + range - 1;
        next_lower_bound = arg->upper_bound + 1;
        
        cout << "Thread " << i 
              << ". Lower bound: " << arg->lower_bound
              << " Upper bound: " << arg->upper_bound << endl;

        // create the thread
        pthread_create(&threadids[i], &attr, runner, (void *) arg);
    }

    // wait for the threads to exit
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threadids[i],NULL);
    }

    int total = 0;
    for(int i = 0; i < NUM_THREADS; ++i) {
        total = total + results[i];
    }
    cout << "Total: " << total << endl;
}


/* The thread will execute in this function */

void *runner(void *param)
{
    thread_args * args = (thread_args*) param;

    results[args->num] = 0;

    for (int i = args->lower_bound; i <= args->upper_bound; ++i ) {
        results[args->num] += i;
    }

    pthread_exit(0);
}

