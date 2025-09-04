#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

pthread_t philosophers[5];
int philosopher_numbers[5] = {0, 1, 2, 3, 4};
sem_t forks[5];

int left(int p) { return p; }
int right(int p) { return (p + 1) % 5; }

void get_forks(int p)
{
    if (p == 5) // key to the solution of the deadlock
    {
        sem_wait(&forks[right(p)]);
        sem_wait(&forks[left(p)]);
    } 
    else
    {
        sem_wait(&forks[left(p)]);
        sem_wait(&forks[right(p)]);
    }
}

void put_forks(int p)
{
    sem_post(&forks[left(p)]);
    sem_post(&forks[right(p)]);
}

void eat(int p)
{
    sleep(1);
    printf("Philosopher %d finished eating\n", p);
}

void think()
{
    sleep(1);
}

void* philosopher_thread(void* args)
{
    int p = *((int*)(args));

    get_forks(p);

    eat(p);

    put_forks(p);

    think();
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher_thread, &philosopher_numbers[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
}