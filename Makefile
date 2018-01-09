CC = gcc

all:
	$(CC) src/main.c -o bin/main

clean:
	rm -rf bin/*
