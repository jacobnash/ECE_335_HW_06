
EXECUTABLES = simulate
CC = gcc -std=c99
LIBS = libfdr.a
CFLAGS = -O2

LIBFDROBJS = dllist.o jval.o

all: $(EXECUTABLES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -w -c $*.c

simulate: simulate.o libfdr.a
	$(CC) $(CFLAGS) -o simulate simulate.o $(LIBS) -lm

libfdr.a: $(LIBFDROBJS)
	ar ru libfdr.a $(LIBFDROBJS)
	ranlib libfdr.a 
clean:
	rm -f core *.o $(EXECUTABLES) *~ libfdr.a

test: simulate
	./simulate 32 16 1 4  4 4
