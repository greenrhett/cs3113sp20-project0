CC = gcc
all: main

main: main.c
	$(CC) -o project0 project0.c

clean:
	rm -f main.o
