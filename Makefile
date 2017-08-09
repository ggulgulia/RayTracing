CC=g++

CFLAGS=-std=c++11 -c -Werror -pedantic -Wall

ifeq ($(mode),debug)                                                                                                                                  
CFLAGS += -O0 -g
else
CFLAGS += -O3
endif 

#linker flags
LDFLAGS=-lm

#OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=raysim

all: $(EXECUTABLE)

$(EXECUTABLE): vectors.o matrix.o ray.o intersection.o shape.o main.o
		$(CC) vectors.o matrix.o ray.o intersection.o shape.o main.o -o $@ $(LDFLAGS) 
		
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
	rm -rf *.o $(EXECUTABLE)
	
	
