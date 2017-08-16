SOURCES= vectors.cpp matrix.cpp matrix2.cpp ray.cpp intersection.cpp shape.cpp camera.cpp #image.cpp 
CC=g++

CFLAGS=-std=c++11 -c -Werror -pedantic -Wall 

ifeq ($(mode),debug)                                                                                                                                  
CFLAGS += -O0 -g
else
CFLAGS += -O3
endif 

#linker flags
LDFLAGS=-lm

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raysim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) main.o
	$(CC) -std=c++11 $(OBJECTS) main.o `libpng-config --ldflags` -o $@ $(LDFLAGS) 
		
$(OBJECTS): %.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@
	
main.o: main.cpp
	$(CC) $(CFLAGS) `libpng-config --ldflags` main.cpp
		
clean:
	rm -f $(OBJECTS) main.o $(EXECUTABLE)
