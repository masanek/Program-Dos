#include "sync_queue.h"
#include "munch1.h"
#include <stdio.h>

struct thread_data
{
    sync_queue * input;
    sync_queue * output;
};

void * munch1(void * data)
{
   char * message = sync_dequeue(((struct thread_data *) data)->input);
   printf("%s",message);
   return NULL;
}
