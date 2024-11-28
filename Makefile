# Simple makefile

CC := g++ -std=c++23 -O2

CCW := -Wall -Werror -Wextra

.DEFAULT_GOAL := main

main:
	$(CC) $(CCW) -o ./bin/main ./src/main.cpp
	./bin/main

clean:
	rm -rf ./bin/main

all: clean main
