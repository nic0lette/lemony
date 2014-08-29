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
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
}

%start_symbol program

program ::= . {
}

program ::= expr(A) NEWLINE. {
    state->result = A;
	state->eval = true;

	std::cout << "Result: " << A.int_value << std::endl;
}

expr(A) ::= INT(B). {
	std::cout << "Reduce: INT" << std::endl;
    A = B;
}

expr(A) ::= expr(B) ADD expr(C). {
	std::cout << "Reduce: ADD" << std::endl;
    A.int_value = B.int_value + C.int_value;
}
expr(A) ::= expr(B) SUB expr(C). {
	std::cout << "Reduce: SUB" << std::endl;
    A.int_value = B.int_value - C.int_value;
}
expr(A) ::= expr(B) MUL expr(C). {
	std::cout << "Reduce: MUL" << std::endl;
    A.int_value = B.int_value * C.int_value;
}
expr(A) ::= expr(B) DIV expr(C). {
	std::cout << "Reduce: DIV" << std::endl;
    A.int_value = B.int_value / C.int_value;
}

expr(A) ::= LPAREN expr(B) RPAREN. {
	std::cout << "Reduce: PARENS" << std::endl;
    A = B;
}
