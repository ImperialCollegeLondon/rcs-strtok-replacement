
CFLAGS = -fPIC -O3

libc-strtok-shim.so: strtok.o
	gcc -fPIC -O3 -shared -o $@ $^
