glibc_install := $(shell pwd)/../../libc/glibc/build/install
pthread: pthread.c
	gcc \
	-L "${glibc_install}/lib" -I "${glibc_install}/include" \
	-Wl,--rpath="${glibc_install}/lib" \
	-Wl,--dynamic-linker="${glibc_install}/lib/ld-linux-x86-64.so.2" \
	-o pthread \
	pthread.c \
	-D_GNU_SOURCE -g \
	-pthread -static

clean:
	rm -f pthread
