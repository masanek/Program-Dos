#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "thread_data.h"
#include "munch1.h"

/*This will read messages from the queue and replace blank characters with * */
void * munch1(void * data)
{
    char * message;
    int done = 1;
    while(done == 1)
    {
        /*Dequeue the next message synchronously*/
        message = sync_dequeue(((thread_data *) data)->input);
        /*Replace spaces and tabs with * */
	if(message != NULL)
	{
            replaceWithStar(message,' ');
            replaceWithStar(message,(char)9);
	}
	else
	{
	    /*When we recieve a null pointer we are finished-clean up memory*/
	    done = 0;
	    free(((thread_data *) data)->input->myQueue->buffer);
	    free(((thread_data *) data)->input->myQueue);
	    free(((thread_data *) data)->input);
	}
	/*Enququq the next message*/
	sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}

/*This function will process a string and replace the parameter char with * */
void replaceWithStar(char * message, char replace)
{
    char * nextBlank;
    nextBlank = index(message,replace);
    while(nextBlank != NULL)
    {
        *nextBlank = '*';
        nextBlank = index(message,replace);
    }
}
