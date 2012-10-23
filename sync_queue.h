#include "queue.h"
#include <semaphore.h>
/*Define our queue struct, but not twice*/
#ifndef cs537_sync_queue
#define cs537_sync_queue
typedef struct cs537_sync_queue /*Tag for the struct*/
{ 
    Queue * myQueue;
    /*Hand off semaphores*/
    sem_t read_wait;
    sem_t write_wait;
}sync_queue;/*Actual struct name*/
#endif

/*This will create a struct with the size parameter,
and will return the point to the allocated Queue*/
sync_queue * sync_create(int);

/*This will add the new message to the Queue only
if there is space*/
void sync_enqueue(sync_queue *,char*);

/*This will remove the next message out of the buffer and 
return it to the calling process.S*/
char * sync_dequeue(sync_queue *);

/*Debugging function for testing Queue, prints the queues contents*/
void sync_printQueue(sync_queue *);
