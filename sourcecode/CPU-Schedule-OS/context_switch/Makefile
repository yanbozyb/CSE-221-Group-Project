context_switch_pthread: context_switch_pthread.c
	gcc -o context_switch_pthread context_switch_pthread.c -lpthread -D_GNU_SOURCE

context_switch_fork: context_switch_fork.c
	gcc -o context_switch_fork context_switch_fork.c -D_GNU_SOURCE

all: context_switch_fork context_switch_pthread

clean:
	rm -f context_switch_fork context_switch_pthread