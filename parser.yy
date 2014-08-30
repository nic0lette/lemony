%token_prefix TOKEN_

%left ADD SUB.
%left MUL DIV.

%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <iostream>
#include "scanner.def.h"
}

%syntax_error {
    std::cerr << "Syntax error" << std::endl;
}

%parse_failure {
    std::cerr << "Giving up.  Parser is hopelessly lost..." << std::endl;
}

%start_symbol statement

statement ::= . {
	// This should just be the EOF
	// Also it seems like we should be able to do this better =/
	state->eval = true;
}

statement ::= declaration NEWLINE. {
	state->eval = true;
}

declaration ::= DEF SYM MAPS function. {
}

declaration ::= DEF SYM MAPS expr. {
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON rhs. {
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON NEWLINE rhs. {
}

arguments_list ::= . {
}

arguments_list ::= SYM arguments_cont. {
}

arguments_cont ::= . {
}

arguments_cont ::= COMMA SYM arguments_cont. {
}

// Right Hand Side (rhs)

// Typical expression
rhs ::= expr. {
}

// lambda function
rhs ::= function. {
}

// Operators
expr ::= expr ADD expr. {
}
expr ::= expr SUB expr. {
}
expr ::= expr MUL expr. {
}
expr ::= expr DIV expr. {
}
expr ::= LPAREN expr RPAREN. {
}

// Unary +/-
expr ::= SUB expr. {
}
expr ::= ADD expr. {
}

// Base symbols
expr ::= INT. {
}
expr ::= SYM. {
}
