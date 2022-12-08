CC=gcc
CFLAGS=-c -Wall -I.

all: main

main: main.c libqueue.a queue.h
	$(CC) main.c -o main -L. -lqueue -I.

libqueue.a: node.o queue.o
	ar -rc libqueue.a node.o queue.o

node.o: node.c node.h
	$(CC) $(CFLAGS) node.c

queue.o: queue.c node.h queue.h
	$(CC) $(CFLAGS) queue.c
