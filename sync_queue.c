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
    sem_init(&(sync_temp->write_wait), 0, size);

    sync_temp->terminate = 0;
    /*Debug*/
    sem_init(&(sync_temp->debug), 0, 0);
    return sync_temp;
}

void sync_destroy(sync_queue * q)
{
    sem_wait(&(q->lock));
    destroy(q->myQueue);
    sem_post(&(q->lock));
    /*Clean up semaphores?*/
}

void sync_enqueue(sync_queue * q, char * message)
{
    /*Add lock incase its full*/
    sem_wait(&(q->write_wait));
    sem_wait(&(q->lock));
    enqueue(q->myQueue,message);
    sem_post(&(q->lock));
    sem_post(&(q->read_wait));
}

char * sync_dequeue(sync_queue * q)
{
    char * message;
    if(q->debug_toggle == 1)
    {
        sem_wait(&(q->debug));
    }
    sem_wait(&(q->read_wait));
    sem_wait(&(q->lock));
    message = dequeue(q->myQueue);
    sem_post(&(q->lock));
    sem_post(&(q->write_wait));
    return message;
}
/*Doesnt work if Queue is full*/
void sync_printQueue(sync_queue * q)
{
    sem_wait(&(q->lock));
    printQueue(q->myQueue);
    sem_post(&(q->lock));
}

void increment_debug(sync_queue * q)
{
    sem_post(&(q->debug));
}
