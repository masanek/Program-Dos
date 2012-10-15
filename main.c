#include <stdio.h>
#include <pthread.h>
#include "reader.h"
#include "queue.h"

#define MAXBUFFER 3

int main()
{
    Queue * q;
pthread_t reader;
    q = create(MAXBUFFER);
    enqueue(q,"Hello");
enqueue(q,"Hello2");
    printQueue(q);
dequeue(q);
dequeue(q);
enqueue(q,"Hello3");
enqueue(q,"False");
printQueue(q);

    /*Create the four threads*/
    if(pthread_create(&reader, NULL, &read, NULL))
    {
        printf("Could not create thread\n");
        return -1;
    }
    /*Wait for them to finish*/
    if(pthread_join(reader, NULL))
    {
        printf("Could not join thread\n");
        return -1;
    }
    return 0;
}
