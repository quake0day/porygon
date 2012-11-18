# Makefile file
# Two mode
# make: output normal version execution file
# make debug: output debug version execution file
CC = gcc
CFLAGS = -O -Wall -lpthread -std=c99 -pedantic -D_XOPEN_SOURCE=600 -pthread
DEBUG = -DDEBUG
virtualmem: main.o fifo.o
	$(CC) $(CFLAGS) -o virtualmem main.o fifo.o

main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

fifo.o:  fifo.c
	$(CC) $(CFLAGS) -c fifo.c
    
# For the debug mode
debug: 
	$(CC) $(CFLAGS) $(DEBUG) -o virtualmem main.c fifo.c

clean:
	@- $(RM) *.o
	@- $(RM) virtualmem
	@- echo "Data Cleansing Done.Ready to Compile"
