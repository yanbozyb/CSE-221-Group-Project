CC = gcc
CFLAGS = -O0 -fno-builtin
LDFLAGS = -lrt
TARGET = mem_latency
OBJS = mem_latency.o

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

mem_latency.o: mem_latency.c
        $(CC) $(CFLAGS) -c $<

clean:
        rm -f $(TARGET) $(OBJS)

.PHONY: clean