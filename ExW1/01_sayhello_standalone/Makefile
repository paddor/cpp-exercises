CC=llvm-g++
CFLAGS=-Wall -std=c++11
LDFLAGS = -L.

default: sayhello
	./sayhello
sayhello: libsayhello.a main.cpp
	$(CC) $(LDFLAGS) -lsayhello main.cpp -o $@

libsayhello.a: sayhello.o
	ar -r $@ sayhello.o

sayhello.o: sayhello.cpp sayhello.hpp
	$(CC) -c -o $@ sayhello.cpp


.PHONY: clean
clean:
	rm -f *.o *.a sayhello
