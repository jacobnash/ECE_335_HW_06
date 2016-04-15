EXECUTABLES = simulate

CC = gcc
LIBS = libfdr.a
CFLAGS = -O2 

LIBFDROBJS = dllist.o  jval.o

all: $(EXECUTABLES) simulate

.SUFFIXES: .c .o
	.c.o:
		$(CC) $(CFLAGS) -w -c $*.c


simulate:  simulate.o libfdr.a
		$(CC) $(CFLAGS) -o simulate  simulate.o $(LIBS) -lm


libfdr.a: $(LIBFDROBJS)
		ar ru libfdr.a $(LIBFDROBJS)
			ranlib libfdr.a 
clean:
		rm -f core *.o $(EXECUTABLES) *~ libfdr.a test*

