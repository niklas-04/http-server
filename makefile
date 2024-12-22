TARGETS = server client
SRCDIR = src
OUTDIR = build
FLAGS = -pedantic

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	gcc $(FLAGS) -c $< -o $@

build: $(OUTDIR)/server

$(OUTDIR)/server:  $(OUTDIR)/server.o $(OUTDIR)/test_server.o $(OUTDIR)/http_parser.o
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f  $(OUTDIR)/server $(OUTDIR)/client $(OUTDIR)/*.o

.PHONY: build clean
