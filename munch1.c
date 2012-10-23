#include "thread_data.h"
#include "munch1.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void * munch1(void * data)
{
    char * message;
    int done = 1;
    while(done == 1)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        /*Replace spaces and tabs with * */
	if(message != NULL)
	{
            replaceWithStar(message,' ');
            replaceWithStar(message,(char)9);
	}
	else
	{
	    done = 0;
	    free(((thread_data *) data)->input->myQueue->buffer);
	    free(((thread_data *) data)->input->myQueue);
	    free(((thread_data *) data)->input);
	}
	sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}

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
