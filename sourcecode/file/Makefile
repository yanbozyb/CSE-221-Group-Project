CC = gcc
CFLAGS = -O0 -fno-builtin
CFLAGS2 = -O3
LDFLAGS = -lrt
TARGET1 = filecache
TARGET2 = filedirect
#TARGET3 = prepare_file
#TARGET4 = pagefault
OBJS1 = filecache.o
OBJS2 = filedirect.o
#OBJS3 = prepare_file.o
#OBJS4 = pagefault.o

all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

#$(TARGET3): $(OBJS3)
#	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

#$(TARGET4): $(OBJS4)
#	$(CC) $(CFLAGS2) -o $@ $^ $(LDFLAGS)

filecache.o: filecache.c
	$(CC) $(CFLAGS) -c $<

filedirect.o: filedirect.c
	$(CC) $(CFLAGS2) -c $<

#prepare_file.o: prepare_file.c
#	$(CC) $(CFLAGS2) -c $<

#pagefault.o: pagefault.c
#	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2)
#clean:
	#rm -f $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2) $(TARGET3) $(OBJS3) $(TARGET4) $(OBJS4)

.PHONY: clean all

