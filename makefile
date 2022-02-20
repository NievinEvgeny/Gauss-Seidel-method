all: matrix.c
		gcc -Wall -o matrix $^ -lm
clean:
		rm matrix