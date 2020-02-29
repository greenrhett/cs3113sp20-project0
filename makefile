CC = gcc
all: main

main: main.o
	$(CC) -o main main.o

clean:
	rm -f main.o
