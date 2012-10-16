#include <stdio.h>
#include <stdlib.h>

#include "sync_queue.h"

sync_queue * sync_create(int size)
{
    sync_queue * sync_temp = malloc(sizeof(sync_queue));
    Queue * temp = create(size);
    
    sync_temp->myQueue = temp;
    
    sem_init(&(sync_temp->lock), 0, 1);
    sem_init(&(sync_temp->read_wait), 0, 0);
    return sync_temp;
}

void sync_destory(sync_queue * q)
{
    sem_wait(&(q->lock));
    destroy(q->myQueue);
    sem_post(&(q->lock));
    /*Clean up semaphores?*/
}

void sync_enqueue(sync_queue * q, char * message)
{
    sem_wait(&(q->lock));
    enqueue(q->myQueue,message);
    sem_post(&(q->read_wait));
    sem_post(&(q->lock));
}

char * sync_dequeue(sync_queue * q)
{
    char * message;
    sem_wait(&(q->read_wait));
    sem_wait(&(q->lock));
    message = dequeue(q->myQueue);
    sem_post(&(q->lock));
    return message;
}
/*Doesnt work if Queue is full*/
void sync_printQueue(sync_queue * q)
{
    sem_wait(&(q->lock));
    printQueue(q->myQueue);
    sem_post(&(q->lock));
}
