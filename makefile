all: build

build:
	gcc -Wall -g -o som main.c -lm
	./som
