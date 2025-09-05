#include <stdio.h>
#include <pthread.h>
#include "future-promise.h"


typedef struct PromiseArg
{
    Promise* promise;
    int value;
} PromiseArg;

void* promise_thread(void* args)
{
    PromiseArg* arg = (PromiseArg*)args;
    Promise* p = (Promise*)(arg->promise);

    set_value(p, arg->value);
}

int main()
{
    for (int i = 0; i < 10000; i++)
    {
        Promise p = init_promise();
        Future f = get_future(&p);
        PromiseArg arg = {&p, i};
        
        pthread_t t1;
        pthread_create(&t1, NULL, promise_thread, &arg);
        pthread_join(t1, NULL);
        
        printf("Value in the future: %d\n", get(&f));
    }
}