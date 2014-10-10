CC = llvm-g++
INCLUDES = -I../../Catch/include
CFLAGS = -Wall $(INCLUDES) -std=c++11
LDFLAGS = -L.

default: test
	./test

test: libhello.a test.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -lhello test.cpp -o $@

libhello.a: hello.o
	ar -r $@ hello.o

hello.o: hello.cpp hello.hpp
	$(CC) $(CFLAGS) -c -o $@ hello.cpp

.PHONY: clean
clean:
	rm -f *.o *.a test
