CC := gcc
CFLAGS := -Wall
LDFLAGS := -lc

connection_overhead_server: connection_overhead_server.c
	$(CC) $(CFLAGS) -o connection_overhead_server connection_overhead_server.c $(LDFLAGS)

connection_overhead_client: connection_overhead_client.c
	$(CC) $(CFLAGS) -o connection_overhead_client connection_overhead_client.c $(LDFLAGS)

all: connection_overhead_client connection_overhead_server

.PHONY: clean
clean:
	rm -rf connection_overhead_server connection_overhead_client
