#include "thread_data.h"
#include "munch2.h"
#include <stdio.h>
#include <ctype.h>

void * munch2(void * data)
{
    char * message;
    int count;
    while(1)
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
        sync_enqueue(((thread_data *) data)->output, message);
   }
}
