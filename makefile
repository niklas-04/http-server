targets = server client

build: server.o
	gcc src/server.o

clean:
	rm -f src/*.o src/server src/client

.PHONY: build clean
