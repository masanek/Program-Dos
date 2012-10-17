#include "thread_data.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

void * write(void * data)
{
    char * message;
    int count;
    while(1)
    {
        message = sync_dequeue(((thread_data *) data)->input);
        count = 0;
        while(message[count] != '\0')
        {
            putchar(message[count]);
            count++;
        }
        putchar('\n');
        /*Free the messages memory*/
        free(message);
    }
    return NULL;
}
