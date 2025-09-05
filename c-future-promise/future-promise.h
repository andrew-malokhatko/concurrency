#ifndef FUTURE_PROMISE
#define FUTURE_PROMISE

#include <pthread.h>
#include <semaphore.h>

typedef struct Promise
{
    sem_t fulfilled;
    int value;
} Promise;


typedef struct Future
{
    sem_t* fulfilled;
    int* value;
} Future;

Promise init_promise();
Future get_future(Promise* p);

void set_value(Promise* p, int value);
int get(Future* f);

#endif