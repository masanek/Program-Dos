#include "queue.h"
#include <semaphore.h>
#include <pthread.h>
/*Define our queue struct, but not twice*/
#ifndef cs537_sync_queue
#define cs537_sync_queue
typedef struct cs537_sync_queue /*Tag for the struct*/
{ 
    Queue * myQueue;
    /*Semaphores for syncing*/
    sem_t lock;
    /*Hand off semaphores*/
    sem_t read_wait;
    sem_t write_wait;
    /*Trigger to release the buffer*/
    int terminate;
    /*Debug semaphore*/
    sem_t debug;
    int debug_toggle;
}sync_queue;/*Actual struct name*/
#endif

/*This will create a struct with the size parameter,
and will return the point to the allocated Queue*/
sync_queue * sync_create(int);

/*Properly clean up the queue's memory*/
void sync_destroy(sync_queue *);

/*This will add the new message to the Queue only
if there is space*/
void sync_enqueue(sync_queue *,char*);

/*This will remove the next message out of the buffer and 
return it to the calling process.S*/
char * sync_dequeue(sync_queue *);

/*Debugging function for testing Queue, prints the queues contents*/
void sync_printQueue(sync_queue *);

/*Debugging function for locking and such*/
void increment_debug(sync_queue * q);
