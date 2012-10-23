#include <stdio.h>
#include <stdlib.h>

#include "thread_data.h"
#include "reader.h"

/*Thread for reading input*/
void * read(void * data)
{   
    int EOF_trigger = 0;
    int null_trigger = 0;
    int count;
    char * word;
    char next;
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
            }
        }
        /*Handle end of file*/
        if(next==EOF)
        {   
            if(count != 0)
	    	putchar('\n');
            EOF_trigger = 1;
        }
        /*Put the message on the queue if everything went ok*/
        if(0 == null_trigger)
        {
            word[count] = '\0';
            sync_enqueue(((thread_data *) data)->output, word);
        }
        else
	{
	    printf("null byte encountered, line ignored\n");
	    free(word);
	}
	if(EOF_trigger == 1)
	{/*Send off a null message indicating terminations*/
	    sync_enqueue(((thread_data *) data)->output, NULL);
	}
    }
    return NULL;
}
