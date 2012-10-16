#include <stdio.h>
#include "sync_queue.h"
#include "reader.h"

void * read(void * data)
{
    printf("Hello world!\n");

    return NULL;
}
