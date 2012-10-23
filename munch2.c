#include "thread_data.h"
#include "munch2.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void * munch2(void * data)
{
    char * message;
    int count;
    int done = 1;
    while(done == 1)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        count = 0;
	if(message != NULL)
	{
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
	    done=0;	
	    free(((thread_data *) data)->input->myQueue->buffer);
	    free(((thread_data *) data)->input->myQueue);
	    free(((thread_data *) data)->input);
	}
	sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}
