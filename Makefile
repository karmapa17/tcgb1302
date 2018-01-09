CC = gcc

all:
	$(CC) -w src/main.c -o bin/main

clean:
	rm -rf bin/*
