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

%start_symbol program

program ::= . {
	// This should just be the EOF
	// Also it seems like we should be able to do this better =/
	std::cout << "Reduce: empty program" << std::endl;
	state->eval = true;
}

program ::= declaration NEWLINE. {
	std::cout << "Reduce: program" << std::endl;
	state->eval = true;
}

declaration ::= DEF SYM MAPS function. {
	std::cout << "Reduce: declaration" << std::endl;
}

declaration ::= DEF SYM MAPS expr. {
	std::cout << "Reduce: declaration" << std::endl;
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON expr. {
	std::cout << "Reduce: function" << std::endl;
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON NEWLINE expr. {
	std::cout << "Reduce: function" << std::endl;
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON function. {
	std::cout << "Reduce: function" << std::endl;
}

function ::= FUNCTION LPAREN arguments_list RPAREN COLON NEWLINE function. {
	std::cout << "Reduce: function" << std::endl;
}

arguments_list ::= . {
	std::cout << "Reduce: empty arguments_list" << std::endl;
}

arguments_list ::= SYM arguments_cont. {
	std::cout << "Reduce: arguments_list" << std::endl;
}

arguments_cont ::= . {
	std::cout << "Reduce: empty arguments_cont" << std::endl;
}

arguments_cont ::= COMMA SYM arguments_cont. {
	std::cout << "Reduce: arguments_cont" << std::endl;
}

// Operators
expr ::= expr ADD expr. {
	std::cout << "Reduce: + operator" << std::endl;
}
expr ::= expr SUB expr. {
	std::cout << "Reduce: - operator" << std::endl;
}
expr ::= expr MUL expr. {
	std::cout << "Reduce: * operator" << std::endl;
}
expr ::= expr DIV expr. {
	std::cout << "Reduce: / operator" << std::endl;
}
expr ::= LPAREN expr RPAREN. {
	std::cout << "Reduce: parens" << std::endl;
}

// Unary +/-
expr ::= SUB expr. {
	std::cout << "Reduce: negative constant value" << std::endl;
}
expr ::= ADD expr. {
	std::cout << "Reduce: explicit positive constant value" << std::endl;
}

// Base symbols
expr ::= INT. {
	std::cout << "Reduce: constant value" << std::endl;
}
expr ::= SYM. {
	std::cout << "Reduce: named value" << std::endl;
}
