glibc_install := $(shell pwd)/
pthread: pthread.c
	gcc \
	-L "./" \
	-Wl,--rpath="./" \
	-Wl,--dynamic-linker="${glibc_install}/ld-linux-x86-64.so.2" \
	-o pthread \
	pthread.c \
	-D_GNU_SOURCE -g \
	-pthread -static

clean:
	rm -f pthread
