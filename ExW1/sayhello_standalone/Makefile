CC=llvm-g++
CFLAGS=-Wall

default: sayhello
	./sayhello
sayhello: sayhello.o mainsayhello.cpp
	$(CC) -L. -lsayhello mainsayhello.cpp -o sayhello

sayhello.o: sayhello.cpp sayhello.hpp
	$(CC) -c -o sayhello.o sayhello.cpp
	ar -r libsayhello.a sayhello.o

.PHONY: clean
clean:
	rm -f *.o *.a sayhello
