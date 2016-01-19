CC = clang++
INCLUDES =
CFLAGS = -Wall -Wextra $(INCLUDES) -std=c++14
LDFLAGS =

default: monsters fizzybubbele multiple_choice
	./monsters
	./fizzybubbele
	./multiple_choice

monsters: monsters.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

fizzybubbele: fizzybubbele.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

multiple_choice: multiple_choice.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f monsters multiple_choice
