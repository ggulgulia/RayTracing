SOURCES= vectors.cpp matrix.cpp matrix2.cpp ray.cpp intersection.cpp shape.cpp main.cpp
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

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 
		
$(OBJECTS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
		
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	
	
