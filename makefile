CC = gcc
FLAGS = -Wall -g

all: frequency
frequency: frequency.c
	$(CC) $(FLAGS) frequency.c -o frequency

.PHONY: clean all

clean:
	rm -f frequency
