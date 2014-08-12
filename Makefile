all: mycalc

mycalc: scanner.h parser.c main.cc
	g++ -o mycalc main.cc

parser.c: parser.yy
	lemon parser.yy

scanner.h: scanner.re scanner.def.h
	re2c scanner.re > scanner.h

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h mycalc

.PHONY: all clean

