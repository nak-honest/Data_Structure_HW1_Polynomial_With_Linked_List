TARGET=main
OBJ=Node.o SinglyLinkedList.o Polynomial.o main.o
CC=g++
CFLAGS=-c

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJ)
