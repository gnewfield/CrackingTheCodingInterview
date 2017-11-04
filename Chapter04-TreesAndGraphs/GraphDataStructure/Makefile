# Make graph data structure test program
CC=gcc
CFLAGS=-I.

%.o: %.c graph.h
	$(CC) -c -o $@ $< $(CFLAGS)

testGraph: graph.o test.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o