#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include "data.h"

int loops = 100000;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;


void* producer(void* args)
{
    for (int i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&lock);
        while (count ==  MAX)
            pthread_cond_wait(&empty, &lock);

        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&lock);
    }   
}

void* consumer(void* args)
{
    for (int i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&lock);
        while (count == 0)
            pthread_cond_wait(&fill, &lock);

        int tmp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);

        printf("Got: %d\n", tmp);
    }   
}


int main()
{
    pthread_t cons1, cons2, cons3, prod1, prod2, prod3;

    pthread_create(&prod1, NULL, producer, NULL);
    pthread_create(&prod2, NULL, producer, NULL);
    pthread_create(&prod3, NULL, producer, NULL);

    pthread_create(&cons1, NULL, consumer, NULL);
    pthread_create(&cons2, NULL, consumer, NULL);
    pthread_create(&cons3, NULL, consumer, NULL);

    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(prod3, NULL);
    pthread_join(cons1, NULL);
    pthread_join(cons2, NULL);
    pthread_join(cons3, NULL);
}