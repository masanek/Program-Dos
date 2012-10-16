#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue * create(int size)
{
    Queue * temp_queue = malloc(sizeof(Queue));
    char ** temp_buffer = malloc(sizeof(char*)*size);

    temp_queue->buffer = temp_buffer;
    temp_queue->head = 0;
    temp_queue->tail = 0;
    temp_queue->buffer_size = size;
    
    return temp_queue;
}

void destroy(Queue * q)
{
    free(q->buffer);/*Not sure if this is 100% correct, might want to add lock*/
    free(q);
}

/*How to handle enqueue more then the buffer size? caller or here?*/
void enqueue(Queue * q, char * message)
{
    (q->buffer)[(q->tail)] = message;
    q->tail = (q->tail+1)%(q->buffer_size);
}

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
