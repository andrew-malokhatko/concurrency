#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "data.h"


int loops = 100000;
sem_t empty;
sem_t full;
sem_t mutex;

void* producer(void* args)
{
    for (int i = 0; i < loops; ++i)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void* cosumer(void* args)
{
    for (int i = 0; i < loops; ++i)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int tmp = get();
        sem_post(&mutex);
        sem_post(&empty);

        printf("%d\n", tmp);
    }
}

int main()
{
    pthread_t p1, p2, c1, c2;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, producer, NULL);

    pthread_create(&c1, NULL, cosumer, NULL);
    pthread_create(&c2, NULL, cosumer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
}