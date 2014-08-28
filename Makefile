GCC = g++
CFLAGS = -I../include/ -O2

all: lemony

lemony: scanner.h parser.c main.cc
	$(GCC) $(CFLAGS) -o lemony main.cc

parser.c: parser.yy scanner.h
	lemon parser.yy

scanner.h: scanner.re scanner.def.h
	re2c scanner.re > scanner.h

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h lemony

.PHONY: all clean

