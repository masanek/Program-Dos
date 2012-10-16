# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
proj2: main.o reader.o queue.o sync_queue.o
	$(CC) $(CFLAGS) main.o reader.o queue.o sync_queue.o -o proj2 -lpthread

reader.o: reader.c 
	$(CC) $(CFLAGS) -c reader.c

munch1.o: munch1.c 
	$(CC) $(CFLAGS) -c munch1.c

munch2.o: munch2.c 
	$(CC) $(CFLAGS) -c munch2.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c -lpthread

sync_queue.o: sync_queue.c
	$(CC) $(CFLAGS) -c sync_queue.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lpthread
