# Makefile file
# Two mode
# make: output normal version execution file
# make debug: output debug version execution file
CC = gcc
CFLAGS = -O -Wall -lpthread -std=c99 -pedantic -D_XOPEN_SOURCE=600 -pthread
DEBUG = -DDEBUG
virtualmem: main.o fifo.o queue.o optimal.o lfu.o lru_clock.o lru_stack.o lru_ref8.o
	$(CC) $(CFLAGS) -o virtualmem main.o fifo.o optimal.o queue.o lfu.o lru_clock.o lru_stack.o lru_ref8.o

main.o:  main.c
	$(CC) $(CFLAGS) -c main.c

fifo.o:  fifo.c
	$(CC) $(CFLAGS) -c fifo.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

optimal.o: optimal.c
	$(CC) $(CFLAGS) -c optimal.c

lfu.o:lfu.c
	$(CC) $(CFLAGS) -c lfu.c
    
lru_stack.o:lru_stack.c
	$(CC) $(CFLAGS) -c lru_stack.c

lru_clock.o:lru_clock.c
	$(CC) $(CFLAGS) -c lru_clock.c

lru_ref8.o: lru_ref8.c
	$(CC) $(CFLAGS) -c lru_ref8.c

# For the debug mode
debug: 
	$(CC) $(CFLAGS) $(DEBUG) -o virtualmem main.c fifo.c queue.c optimal.c lfu.c lru_clock.c lru_stack.c lru_ref8.c

clean:
	@- $(RM) *.o
	@- $(RM) virtualmem
	@- echo "Data Cleansing Done.Ready to Compile"
