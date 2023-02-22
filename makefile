CC=gcc
CFLAGS=-g -Wall

default: bamazon

bamazon: main.o bamazon.o
	$(CC) $(CFLAGS) -o bamazon main.o bamazon.o

main.o: main.c bamazon.h
	$(CC) $(CFLAGS) -c main.c

bamazon.o: bamazon.c bamazon.h
	$(CC) $(CFLAGS) -c bamazon.c

clean: 
	rm -f bamazon *.o
