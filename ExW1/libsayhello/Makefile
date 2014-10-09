CC = llvm-g++
INCLUDES = -ICatch/include
CFLAGS = -Wall $(INCLUDES) -std=c++11
LDFLAGS = -L.

default: test
	./test

test: sayhello.o libsayhello.a test.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -lsayhello test.cpp -o $@

libsayhello.a: sayhello.o
	ar -r libsayhello.a sayhello.o

sayhello.o: sayhello.cpp sayhello.hpp
	$(CC) $(CFLAGS) -c -o $@ sayhello.cpp

.PHONY: clean
clean:
	rm -f *.o *.a test
