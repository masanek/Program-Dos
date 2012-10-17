#include "thread_data.h"
#include "munch1.h"
#include <stdio.h>
#include <strings.h>

void * munch1(void * data)
{
    char * message;
    char * nextBlank;
    while(1)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        nextBlank = index(message,' ');
        while(nextBlank != NULL)
        {
            *nextBlank = '*';
            nextBlank = index(message,' ');
        }
        sync_enqueue(((thread_data *) data)->output, message);
   }
   return NULL;
}
