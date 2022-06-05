all: game

main.o:	main.c

test.o:	test.c test.h
		gcc -c test.c -o test.o

game:		main.o test.o 
		gcc main.o     test.o -o game
