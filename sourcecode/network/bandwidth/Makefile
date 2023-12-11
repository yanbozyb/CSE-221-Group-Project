CC := gcc
CFLAGS := -Wall
LDFLAGS := -lc

bandwidth_server: bandwidth_server.c
	$(CC) $(CFLAGS) -o bandwidth_server bandwidth_server.c $(LDFLAGS)

bandwidth_client: bandwidth_client.c
	$(CC) $(CFLAGS) -o bandwidth_client bandwidth_client.c $(LDFLAGS)

all: bandwidth_client bandwidth_server

.PHONY: clean
clean:
	rm -rf bandwidth_server bandwidth_client
