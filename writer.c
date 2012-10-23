#include <stdio.h>
#include <stdlib.h>

#include "thread_data.h"
#include "writer.h"

/*Reads from munch2 and outputs the final message*/
void * write(void * data)
{
    char * message;
    int count = 0;
    int done = 1;
    while(done == 1)
    {
        message = sync_dequeue(((thread_data *) data)->input);
	if(message != NULL)
        {
	    if (*message != '\0') 
	    {
	        printf("%s\n", message);
	        count++;
	    }
            /*Free the messages memory*/
            free(message);
	}
        else
        {
	    /*Null message encountered, free up memory and exit*/
            printf("%s - %i\n", "Total Number of messages printed", count);
	    done = 0;
	    free(((thread_data *) data)->input->myQueue->buffer);
	    free(((thread_data *) data)->input->myQueue);
	    free(((thread_data *) data)->input);
        }
    }
    return NULL;
}
