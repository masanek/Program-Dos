# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
proj2: main.o reader.o queue.o
	$(CC) $(CFLAGS) main.o reader.o queue.c -o proj2 -lpthread

reader.o: reader.c 
	$(CC) $(CFLAGS) -c reader.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c
