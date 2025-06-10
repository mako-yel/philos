#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

void    *thread_function(void *arg)
{
    // pthread_mutex_lock(&lock); // lock the mutex
    printf("Thread %d has started\n", *(int*)arg);
    // critical section
    printf("Thread %d has finished\n", *(int*)arg);
    // pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void)
{
    pthread_t   threads[2];
    int         threads_ids[2] = {1, 2};

    // // initialize the mutex
    // if (pthread_mutex_init(&lock, NULL) != 0)
    // {
    //     printf("Mutex init failed\n");
    //     return 1;
    // }--

    // create the threads
    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&threads[i], NULL, thread_function, &threads_ids[i]) != 0)
        {
            printf("Thread creation failed !!\n");
            return 1;
        }
    }
    // wait for threads to finish
    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);
    // destroy the mutex
    // pthread_mutex_destroy(&lock);
    // return 5;
}

