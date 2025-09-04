#include "data.h"
#include <assert.h>

int count = 0;
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;

void put(int value)
{
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get()
{
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}