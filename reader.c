#include <stdio.h>
#include <stdlib.h>
#include "thread_data.h"
#include "reader.h"

void * read(void * data)
{   
    int EOF_trigger = 0;
    int null_trigger = 0;
    int count;
    char * word;
    char next;

    /*debug count*/
    int debugC = 0;
    while(0 == EOF_trigger)
    {
        null_trigger = 0;
        EOF_trigger = 0;
        /*Allocate the next message*/
        word = malloc(sizeof(char)*64);
        /*Read in the message*/
        for(count = 0; count < 63; count++)
        {
            next = getchar();
            /*Check for bad characters*/
            /*If a null byte occurs at anytime - we should reject*/
            if('\0' == next)
            {
                null_trigger = 1;
                break;
            }
            else if('\n' == next || EOF == next) /*Entered less then 63 characters*/
            {
                break;
            }     
            else
            {
                word[count] = next;
            }
        }
        /*Finish reading in the queue if necessary*/
        while('\n' != next && EOF != next)
        {
            next = getchar();
            if('\0' == next)
            {
                null_trigger=1;
                break;
            }
        }
        if(next==EOF)
        {   
            EOF_trigger = 1;
        }
        /*Put the message on the queue if everything went ok*/
        if(0 == null_trigger)
        {
            debugC++;
            word[count] = '\0';
            if(EOF_trigger)
	    {   /*Tell the next person we are finished*/
	        ((thread_data *) data)->output->terminate = 1;
            }
            sync_enqueue(((thread_data *) data)->output, word);
        }
        if(debugC==5)
        {
            for(debugC=5; debugC>0; debugC--)
            {
                 increment_debug(((thread_data *) data)->output);     
            }
        }
    }
    return NULL;
}
