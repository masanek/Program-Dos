#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/*Allocates all necessary memory for queue management*/
Queue * create(int size)
{
    Queue * temp_struct = malloc(sizeof(Queue));
    char ** temp_queue;
    if(temp_struct == NULL)
    {
        return NULL;
    }
    temp_queue = malloc(sizeof(char*)*size);
    if(temp_queue == NULL)
    {
        free(temp_struct);
        return NULL;
    }
    temp_struct->buffer = temp_queue;
    temp_struct->head = 0;
    temp_struct->tail = 0;
    temp_struct->buffer_size = size;

    return temp_struct;
}

/*Enqueues a message. This doesnt care if there is over flow*/
void enqueue(Queue * q, char * message)
{
    (q->buffer)[(q->tail)] = message;
    q->tail = (q->tail+1)%(q->buffer_size);
}
/*Dequeue the next message and returns the string. Doesnt worry if empty*/
char * dequeue(Queue * q)
{
    char * message;
    /*I dont worry about the state of the Queue, overwrite later
      Just return and move the head*/
 
    message = (q->buffer)[q->head];
    q->head = (q->head+1)%(q->buffer_size);

    return message;
}
/*Doesnt work if Queue is full*/
void printQueue(Queue * q)
{
    int head = q->head;
    int tail = q->tail;
    int count;
    for(count = head; count%(q->buffer_size)!=tail; count++)
    {
        printf("%s",(q->buffer)[count%(q->buffer_size)]);
    }
}
