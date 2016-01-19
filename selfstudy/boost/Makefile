CC = clang++
INCLUDES =
CFLAGS = -Wall -Wextra $(INCLUDES) -std=c++14
LDFLAGS = -lboost_system -lboost_filesystem

default: filesystem
	./filesystem Makefile

filesystem: filesystem.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f filesystem
