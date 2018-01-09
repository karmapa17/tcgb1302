CC = gcc

all:
	$(CC) -g -w src/main.c -o bin/main

clean:
	rm -rf bin/*
