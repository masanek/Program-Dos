/*Define our thread data struct, but not twice (?)*/
#include "sync_queue.h"
#ifndef cs537_thread_data
#define cs537_thread_data
typedef struct cs537_thread_data
{
    /*We need this struct to pass our thread multiple parameters*/
    sync_queue * input;
    sync_queue * output;
}thread_data;
#endif
