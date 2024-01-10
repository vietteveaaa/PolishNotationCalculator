CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES = graph.c parsing.c stack.c RPN.c drawing.c
RESULT = ../build/graph

all: build

build:
	$(CC) $(CFLAGS) $(SOURCES) -o $(RESULT)

clean:
	rm -rf $(RESULT)

rebuild: clean all