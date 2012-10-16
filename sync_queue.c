#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "sync_queue.h"

sync_queue * sync_create(int size)
{
    return 1;
}

void sync_destory(sync_queue * q)
{
}

void sync_enqueue(sync_queue * q, char * message)
{
}

char * sync_dequeue(sync_queue * q)
{
    return "0";
}
/*Doesnt work if Queue is full*/
void sync_printQueue(sync_queue * q)
{
}
