CC = gcc
all: main

main: main.c
	$(CC) -o project0 main.c

clean:
	rm -f main.o
