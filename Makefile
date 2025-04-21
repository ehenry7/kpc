# Makefile for kpc project (macOS arm64)

CC=clang
CFLAGS=-O2 -Wall -Wextra -target arm64-apple-macos11
LDFLAGS=
LIBS=

OBJS= kpc_main.o kpc_demo1.o kpc_demo2.o kpc_kperf.o kpc_kperfdata.o kpc_dynload.o kpc_kdebug.o

.PHONY: all clean

all: kpc

kpc: $(OBJS)
	$(CC) $(CFLAGS) -o kpc $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o kpc