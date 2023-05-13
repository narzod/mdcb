CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: mdcb

mdcb: main.o
	$(CC) $(CFLAGS) main.o -o mdcb

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o
