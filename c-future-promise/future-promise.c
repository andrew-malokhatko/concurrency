#include "future-promise.h"
#include <stdlib.h>

Promise init_promise()
{
    Promise p;
    sem_init(&p.fulfilled, 0, 0);
    p.value = 0;

    return p;
}

Future get_future(Promise* p)
{
    Future f;
    f.fulfilled = &(p->fulfilled);
    f.value = &(p->value);
    return f;
}

void set_value(Promise* p, int value)
{
    p->value = value;
    sem_post(&p->fulfilled);
}

int get(Future* f)
{
    sem_wait(f->fulfilled);
    return *(f->value);
}