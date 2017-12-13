# Make linked list data structure test program
CC=gcc
CFLAGS=-I.

%.o: %.c linkedList.h
	$(CC) -g -c -o $@ $< $(CFLAGS)

testLinkedList: linkedList.o test.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o