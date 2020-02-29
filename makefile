all: project0.c
	gcc -g -Wall -o project0 project0.c
clean:
	$(RM) project0
