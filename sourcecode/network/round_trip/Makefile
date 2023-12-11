CC := gcc
CFALGS := -Wall


round_trip_server: round_trip_server.c
	$(CC) $(CFALGS) -o $@ $^

round_trip_client: round_trip_client.c
	$(CC) $(CFALGS) -o $@ $^

all: round_trip_client round_trip_server

.PHONY: clean
clean:
	rm -rf round_trip_server round_trip_client

