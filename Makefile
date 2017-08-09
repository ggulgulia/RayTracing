all: trace

trace: vectors.o matrix.o ray.o intersection.o shape.o main.o
		g++ -std=c++11 vectors.o matrix.o ray.o intersection.o shape.o main.o -o trace
		
main.o: main.cpp
		g++ -std=c++11 -c main.cpp
		
vectors.o: vectors.cpp
		g++ -std=c++11 -c vectors.cpp
		
matrix.o: matrix.cpp matrix2.cpp
		g++ -std=c++11 -c matrix.cpp matrix2.cpp
		
intersection.o: intersection.cpp
		g++ -std=c++11 -c intersection.cpp
		
shape.o: shape.cpp
		g++ -std=c++11 -c shape.cpp
		
clean:
	rm -rf *.o *trace
