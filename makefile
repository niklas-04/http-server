TARGETS = server client
DIRECTORY = src/
FLAGS = -pedantic


%.o: %.c
	gcc $(FLAGS) $< -c

build: server.o test_server.o
	gcc $(FLAGS) $(DIRECTORY)$^ -o server

clean:
	rm -f src/*.o src/server src/client

.PHONY: build clean
