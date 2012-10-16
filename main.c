#include <stdio.h>
#include <pthread.h>
#include "sync_queue.h"
#include "reader.h"

#define MAXBUFFER 4

int main()
{
    sync_queue * q;
    pthread_t reader;
    q = sync_create(MAXBUFFER);
    sync_enqueue(q,"Hello");
    sync_enqueue(q,"Hello2");
    sync_printQueue(q);
    sync_dequeue(q);
    sync_dequeue(q);
    sync_enqueue(q,"Hello3");
    sync_enqueue(q,"False");
    sync_printQueue(q);

    /*Create the three queue for messaging*/

    /*Create the four threads
    if(pthread_create(&reader, NULL, &read, NULL))
    {
        printf("Could not create thread\n");
        return -1;
    }
    Wait for them to finish
    if(pthread_join(reader, NULL))
    {
        printf("Could not join thread\n");
        return -1;
    }*/
    return 0;
}
