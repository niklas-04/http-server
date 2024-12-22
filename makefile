TARGETS = server client
SRCDIR = src
OUTDIR = build
FLAGS = -pedantic

$(OUTDIR)/%.o: $(SRCDIR)/%.c | build_dir
	gcc $(FLAGS) -c $< -o $@

build: $(OUTDIR)/server

build_dir:
	mkdir -p $(OUTDIR)

$(OUTDIR)/server:  $(OUTDIR)/server.o $(OUTDIR)/test_server.o $(OUTDIR)/http_parser.o
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f  $(OUTDIR)/server $(OUTDIR)/client $(OUTDIR)/*.o
	rmdir $(OUTDIR)

.PHONY: build clean
