#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define ITERS 10000000


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int counter_r = 0;
int counter_nor = 0;

void* counter_race(void* args)
{
    for (int i = 0; i < ITERS; i++)
    {
        counter_r++;
    }

    for(int i = 0; i < ITERS; i++)
    {
        counter_r--;
    }
}


void* counter_no_race(void* args)
{
    for (int i = 0; i < ITERS; i++)
    {
        pthread_mutex_lock(&lock);
        counter_nor++;
        pthread_mutex_unlock(&lock);
    }

    for(int i = 0; i < ITERS; i++)
    {
        pthread_mutex_lock(&lock);
        counter_nor--;
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_t t1, t2, t3, t4;

    printf("benchmark for atomic and non atomic counter:\n\n");
    
    
    // Counter with race condition
    clock_t start_race = clock();

    pthread_create(&t1, NULL, counter_race, NULL);
    pthread_create(&t2, NULL, counter_race, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    clock_t end_race = clock();
    float seconds = (float)(end_race - start_race) / CLOCKS_PER_SEC;
    
    printf("Counter race: %d\n", counter_r);
    printf("Took %f seconds\n\n", seconds);

    // Counter with no race condition
    start_race = clock();

    pthread_create(&t3, NULL, counter_no_race, NULL);
    pthread_create(&t4, NULL, counter_no_race, NULL);

    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    end_race = clock();
    seconds = (float)(end_race - start_race) / CLOCKS_PER_SEC;
    
    printf("No counter race: %d\n", counter_nor);
    printf("Took %f seconds\n\n", seconds);

    assert(counter_nor == 0);
}