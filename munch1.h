/*munch1 will wait for the next message on the queue synchronously
It will replace all spaces and tabs with * */
void * munch1(void *);
/*A helper function for munch1. It takes in a string pointer and will
replace each specified char with a * */
void replaceWithStar(char *, char);
