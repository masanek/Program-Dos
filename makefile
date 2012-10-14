# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
proj2: main.o reader.o
	$(CC) $(CFLAGS) main.o reader.o -o proj2

reader.o: reader.c 
	$(CC) $(CFLAGS) -c reader.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
