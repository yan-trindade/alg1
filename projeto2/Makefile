all: avl.o rb.o set.o main.o
	gcc avl.o rb.o main.o set.o -o main -std=c99 -Wall
	rm *.o

set.o:
	gcc -c set.c -o set.o

avl.o:
	gcc -c avl.c -o avl.o

rb.o:
	gcc -c rb.c -o rb.o

main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o main

run:
	./main
