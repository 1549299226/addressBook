cc = gcc
TARGET = main
OBJ = main.o addressBook.o balanceBinarySearchTree .o doubleLinkList.o doubleLinkListQueue.o

$(TARGET):$(OBJ)
	$(cc) -o $(TARGET) $(OBJ)

%.o: %.c $(TARGET.H)
	$(cc) -c $< -o $@

clean:
	rm -rf $(OBJ) $(prom)



## main:main.c addressBook.c balanceBinarySearchTree .c doubleLinkList.c doubleLinkListQueue.c
#	main.o addressBook.o balanceBinarySearchTree .o doubleLinkList.o doubleLinkListQueue.o -o main

