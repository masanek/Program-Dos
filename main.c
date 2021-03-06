#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "sync_queue.h"
#include "thread_data.h"
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"

#define MAXBUFFER 10

void cleanUp(sync_queue * q)
{
    if(q!=NULL)
    {
        free(q->myQueue->buffer);
	free(q->myQueue);
	free(q);
    }
}

int main()
{
    /*We should make some crazy enums and generate all this code below! Possible*/
    /*The three syncronized queues to message passing*/
    sync_queue * readerToMunch1;
    sync_queue * munch1ToMunch2;
    sync_queue * munch2ToWriter;
    /*The four threads that will be running*/
    pthread_t reader;
    pthread_t munch1Thread;
    pthread_t munch2Thread;
    pthread_t writerThread;
    /*Structs for passing multiple arguments to the threads*/
    thread_data readerData;
    thread_data munch1Data;
    thread_data munch2Data;
    thread_data writerData;
    /*Initialize all the queues*/
    readerToMunch1 = sync_create(MAXBUFFER);
    munch1ToMunch2 = sync_create(MAXBUFFER);
    munch2ToWriter = sync_create(MAXBUFFER);
    
    if(readerToMunch1 == NULL || munch1ToMunch2 == NULL || munch2ToWriter == NULL)
    {
        cleanUp(readerToMunch1);
        cleanUp(munch1ToMunch2);
        cleanUp(munch2ToWriter);
	printf("Memory issue");
	return -1;
    }
    /*Set up argument structs*/
    readerData.input = NULL;
    readerData.output = readerToMunch1;
    munch1Data.input = readerToMunch1;
    munch1Data.output = munch1ToMunch2;
    munch2Data.input = munch1ToMunch2;
    munch2Data.output = munch2ToWriter;
    writerData.input = munch2ToWriter;
    writerData.output = NULL;

    /*Create the four threads*/
    if(pthread_create(&reader, NULL, &read, (void *)&readerData))
    {
        printf("Could not create reader thread\n");
        return -1;
    }
    if(pthread_create(&munch1Thread, NULL, &munch1, (void *)&munch1Data))
    {
        printf("Could not create munch1\n");
        return -1;
    }
    if(pthread_create(&munch2Thread, NULL, &munch2, (void *)&munch2Data))
    {
        printf("Could not create munch2\n");
        return -1;
    }
    if(pthread_create(&writerThread, NULL, &write, (void *)&writerData))
    {
        printf("Could not create writer\n");
        return -1;
    }
    
    /*Wait for them to finish*/
    if(pthread_join(reader, NULL) || pthread_join(munch1Thread, NULL) || pthread_join(munch2Thread, NULL) || pthread_join(writerThread, NULL))
    {
        printf("Could not join thread\n");
        return -1;
    }
    return 0;
}
