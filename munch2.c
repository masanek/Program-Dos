#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "thread_data.h"
#include "munch2.h"

/*This will read messages off the queue and change all lower case to upper case*/
void * munch2(void * data)
{
    char * message;
    int count;
    int done = 1;
    while(done == 1)
    {
	/*Dequeue synchronously*/
        message = sync_dequeue(((thread_data *) data)->input);
        count = 0;
	if(message != NULL)
	{
	    /*Replace all lower cases with upper cases*/
            while(message[count] != '\0')
            {
                if(islower(message[count]))
                {
                    message[count] = toupper(message[count]);
                }
                count++;
	    }
        }
	else
	{
	    /*Same as munch1. we hit a null string and we need to clean up before exiting*/
	    done=0;	
	    free(((thread_data *) data)->input->myQueue->buffer);
	    free(((thread_data *) data)->input->myQueue);
	    free(((thread_data *) data)->input);
	}
	/*Pass along the next message*/
	sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}
