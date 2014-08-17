GCC = g++
CFLAGS = -O2
OBJS = obj/main.o

all: lemony

lemony: $(OBJS)
	g++ $(CFLAGS) -o lemony $(OBJS)

obj/main.o: src/main.cc src/scanner.h src/parser.c
	g++ $(CFLAGS) -c src/main.cc -o obj/main.o

src/parser.c: src/parser.yy src/scanner.h
	lemon src/parser.yy

src/scanner.h: src/scanner.re src/scanner.def.h src/astnode.h
	re2c src/scanner.re > src/scanner.h

clean:
	rm -rf obj/*.o src/parser.h src/parser.c src/parser.out src/parser.c src/scanner.h lemony

.PHONY: all clean

