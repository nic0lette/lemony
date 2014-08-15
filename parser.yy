%token_prefix TOKEN_

%left ADD SUB.
%left MUL DIV.

%token_type { BaseNode * }

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

program ::= expr(A) SEMI. {
    state->result = A;
	state->eval = 1;
}

expr(A) ::= INT(B). {
    A = B;
}

expr(A) ::= expr(B) ADD expr(C). {
    A = new BinaryOpNode(ADD, B, C);
}
expr(A) ::= expr(B) SUB expr(C). {
    A = new BinaryOpNode(SUB, B, C);
}
expr(A) ::= expr(B) MUL expr(C). {
    A = new BinaryOpNode(MUL, B, C);
}
expr(A) ::= expr(B) DIV expr(C). {
    A = new BinaryOpNode(DIV, B, C);
}

expr(A) ::= LPAREN expr(B) RPAREN. {
    A = B;
}
