CC = clang++
INCLUDES =
CFLAGS = -Wall -Wextra $(INCLUDES) -std=c++14
LDFLAGS =

default: foo
	./foo

foo: foo.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f foo
