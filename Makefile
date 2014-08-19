GCC = g++
CFLAGS = -O2
LD_FLAGS = -Lobj/
OBJS = obj/main.o

all: lemony

lemony: $(OBJS)
	g++ $(LD_FLAGS) -o lemony $(OBJS) -last

obj/main.o: src/main.cc src/scanner.h src/parser.c
	g++ $(CFLAGS) -c src/main.cc -o obj/main.o

src/parser.c: src/parser.yy src/scanner.h
	lemon src/parser.yy

src/scanner.h: src/scanner.re src/scanner.def.h obj/libast.a
	re2c src/scanner.re > src/scanner.h

clean:
	rm -rf lemony obj/*.o obj/*.a \
	src/parser.h src/parser.c src/parser.out src/parser.c \
	src/ast.h src/scanner.h
	
#
# AST Rules
#

CPP_FILES := $(wildcard src/ast/*.cc)
OBJ_FILES = $(patsubst src/ast/%.cc,obj/%.o,$(CPP_FILES))

obj/libast.a: $(OBJ_FILES)
	ar rvs obj/libast.a $(OBJ_FILES)
	ls -1 src/ast/*.h | sed -e 's/src\//#include \"/' -e 's/$$/\"/' | \
		awk 'BEGIN{print "#ifndef AST_H_\n#define AST_H_";}{print $0;}END{print "#endif"}' \
		> src/ast.h

obj/%.o: src/ast/%.cc
	g++ $(CC_FLAGS) -c -o $@ $<

CC_FLAGS += -MMD
-include $(OBJFILES:.o=.d)

.PHONY: all clean

