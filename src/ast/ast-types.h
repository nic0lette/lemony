#ifndef AST_TYPES_H_
#define AST_TYPES_H_

#include <string>

// Operators
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4

// Operator "names"
const char OP_NAMES[] = {'+', '-', '*', '/', '%'};

// Types
#define VOID 0
#define INT 1
#define FLOAT 2
#define BOOL 3
#define STRING 4

const std::string TYPE_NAMES[] = {"void","int","float","bool","string"};

#endif