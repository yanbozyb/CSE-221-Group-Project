CC = gcc
CFLAGS = -O0 -fno-builtin
CFLAGS2 = -O3
LDFLAGS = -lrt
TARGET1 = ram_access_time
TARGET2 = ram_bandwidth
TARGET3 = prepare_file
TARGET4 = pagefault
OBJS1 = ram_access_time.o
OBJS2 = ram_bandwidth.o
OBJS3 = prepare_file.o
OBJS4 = pagefault.o

all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

$(TARGET3): $(OBJS3)
	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

$(TARGET4): $(OBJS4)
	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

ram_access_time.o: ram_access_time.c
	$(CC) $(CFLAGS) -c $<

ram_bandwidth.o: ram_bandwidth.c
	$(CC) $(CFLAGS2) -c $<

prepare_file.o: prepare_file.c
	$(CC) $(CFLAGS2) -c $<

pagefault.o: pagefault.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2) $(TARGET3) $(OBJS3) $(TARGET4) $(OBJS4)

.PHONY: clean all

