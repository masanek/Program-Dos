#include "thread_data.h"
#include "munch1.h"
#include <stdio.h>
#include <strings.h>

void * munch1(void * data)
{
    char * message;
    int done = 1;
    while(done)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        /*Replace spaces and tabs with **/
        replaceWithStar(message,' ');
        replaceWithStar(message,(char)9);
        if(((thread_data *) data)->input->terminate == 1)
        {
            ((thread_data *) data)->output->terminate = 1;
	    done = 0;
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
