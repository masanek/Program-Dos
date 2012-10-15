/*Define our queue struct, but not twice*/
#ifndef cs537_Queue
#define cs537_Queue
typedef struct cs537_Queue /*Tag for the struct*/
{ 
    char** buffer;
    int head;
    int tail;
    int buffer_size;
}Queue;/*Actual struct name*/
#endif

/*This will create a struct with the size parameter,
and will return the point to the allocated Queue*/
Queue * create(int);

/*Properly clean up the queue's memory*/
void destroy(Queue *);

/*This will add the new message to the Queue only
if there is space*/
void enqueue(Queue *,char*);

/*This will remove the next message out of the buffer and 
return it to the calling process.S*/
char * dequeue(Queue *);

/*Debugging function for testing Queue, prints the queues contents*/
void printQueue(Queue *);
