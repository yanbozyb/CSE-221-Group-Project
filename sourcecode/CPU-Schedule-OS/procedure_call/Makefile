CC = gcc
CFLAGS = -Wall -O0

pcall: pcall.c asm.S
	$(CC) $(CFLAGS) -o $@ $^ -D_GNU_SOURCE

rdtscoverhead: rdtscoverhead.c
	$(CC) $(CFLAGS) -o $@ $^ -D_GNU_SOURCE

all: pcall rdtscoverhead

.PHONY: clean
clean:
	rm -f pcall rdtscoverhead
