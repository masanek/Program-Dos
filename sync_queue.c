#include <stdio.h>
#include <stdlib.h>

#include "sync_queue.h"

sync_queue * sync_create(int size)
{
    sync_queue * sync_temp = malloc(sizeof(sync_queue));
    sync_temp->myQueue = create(size);
    
    sem_init(&(sync_temp->lock), 0, 1);
    sem_init(&(sync_temp->read_wait), 0, 0);
    sem_init(&(sync_temp->write_wait), 0, size);
    return sync_temp;
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
