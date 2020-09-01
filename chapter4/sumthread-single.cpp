#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // This data is shared by all threads

void *runner(void *param); // Threads execute this function

int main(int argc, char *argv[])
{
    pthread_t tid; // The thread identifier

    pthread_attr_t attr; // Thread attributes

    // set the default attributes of the thread
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, runner, argv[1]);

    // wait for the thread to exit
    pthread_join(tid,NULL);

    printf("sum = %d\n",sum);
}


/* The thread will execute in this function */

void *runner(void *param)
{
    int i, upper = atoi((const char *) param);
    sum = 0;
    for (i = 1; i <= upper; i++) {
        sum += i;
    }

    pthread_exit(0);
}

