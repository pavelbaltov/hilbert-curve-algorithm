CC=gcc
CFLAGS=-I -O3 -Wall -Wextra -g
all: runhilbert

main.o: main.c coord_t.h
	$(CC) -c $^ $(CFLAGS)

hilbertV2.o: hilbertV2.c hilbertV2.h
	$(CC) -c  $^ $(CFLAGS)

hilbertV1.o: hilbertV1.s 
	$(CC) -c -o $@ $^ $(CFLAGS)

hilbert.o: hilbert.s
	$(CC) -c $^ $(CFLAGS)

runhilbert: hilbert.o main.o hilbertV1.o hilbertV2.o
	$(CC) -o $@ $^ $(CFLAGS) -lm


.PHONY: clean

clean:
	rm -f *.o *.gch
	rm -rf *.dSYM
	rm runhilbert


