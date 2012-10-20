#include "thread_data.h"
#include "munch2.h"
#include <stdio.h>
#include <ctype.h>

void * munch2(void * data)
{
    char * message;
    int count;
    int done = 1;
    while(done)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        count = 0;
        while(message[count] != '\0')
        {
            if(islower(message[count]))
            {
                message[count] = toupper(message[count]);
            }
            count++;
        }
        if(((thread_data *) data)->input->terminate == 1)
        {
            ((thread_data *) data)->output->terminate = 1;
	    done = 0;
        }
        sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}
