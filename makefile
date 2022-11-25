restaurant.o: restaurant.c restaurant.h
	gcc -Wall -c restaurant.c

ArrayList.o: ArrayList.c ArrayList.h
	gcc -Wall -c ArrayList.c

BinaryTree.o: BinaryTree.c BinaryTree.h
	gcc -Wall -c BinaryTree.c

file.o: file.c file.h
	gcc -Wall -c file.c

main.o: main.h main.c
	gcc -Wall -c main.c

main: main.o file.o BinaryTree.o ArrayList.o restaurant.o
	 gcc -Wall main.o file.o BinaryTree.o ArrayList.o restaurant.o -o main

clean:
	rm -f main.o file.o BinaryTree.o ArrayList.o restaurant.o *~ 