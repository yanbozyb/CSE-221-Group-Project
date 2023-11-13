CC = gcc
CFLAGS = -O0 -fno-builtin
CFLAGS2 = -O3
LDFLAGS = -lrt
TARGET1 = ram_access_time
TARGET2 = ram_bandwidth
OBJS1 = ram_access_time.o
OBJS2 = ram_bandwidth.o

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ram_access_time.o: ram_access_time.c
	$(CC) $(CFLAGS) -c $<

ram_bandwidth.o: ram_bandwidth.c
	$(CC) $(CFLAGS2) -c $<

clean:
	rm -f $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2)

.PHONY: clean all

