CC=g++

CFLAGS=-std=c++11 -c -Werror -pedantic -Wall

all: trace

trace: vectors.o matrix.o ray.o intersection.o shape.o main.o
		$(CC) vectors.o matrix.o ray.o intersection.o shape.o main.o -o trace
		
main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp
		
vectors.o: vectors.cpp
		$(CC) $(CFLAGS) vectors.cpp
		
matrix.o: matrix.cpp matrix2.cpp
		$(CC) $(CFLAGS) matrix.cpp matrix2.cpp
		
intersection.o: intersection.cpp
		$(CC) $(CFLAGS) intersection.cpp
		
shape.o: shape.cpp
		$(CC) $(CFLAGS) shape.cpp
		
clean:
	rm -rf *.o *trace
