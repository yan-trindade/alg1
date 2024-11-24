all: avl.o set.o main.o
	gcc avl.o main.o set.o -o main -std=c99 -Wall
	rm *.o

set.o:
	gcc -c set.c -o set.o

avl.o:
	gcc -c avl.c -o avl.o

main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o main

run:
	./main

zip:
	zip -R compacto.zip . '*.c' . '*.h' 'Makefile'

rm:
	rm compacto.zip

desk:
	cp compacto.zip /mnt/c/Users/Yan/Desktop/
