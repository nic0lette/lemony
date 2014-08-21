%token_prefix TOKEN_

%left ADD SUB.
%left MUL DIV MOD.

%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <iostream>
#include "scanner.def.h"
}

%syntax_error {
	fprintf(stderr, "Unexpected token '%s' (following '%s') on line %d\n",
		state->curSym.c_str(), state->prevSym.c_str(), state->line);
}

%parse_failure {
	fprintf(stderr, "Failed to parse line %d\n", state->line);
	state->parseError = 1;
}

%start_symbol program
	
program ::= statement(A). {
    state->astRoot = A;
}

statement(A) ::= SEMI. {
	// Do we want to support empty statements?
	A = new IntNode(0);
}

statement(A) ::= expr(B) SEMI. {
	A = B;
}

statement ::= TYPE(A) IDENTIFIER(B) SEMI. {
	LightweightTypeNode * typeNode = dynamic_cast<LightweightTypeNode *>(A);
	IdentifierNode * idNode = dynamic_cast<IdentifierNode *>(B);
	
	if (typeNode == 0 || idNode == 0) {
		cerr << "internal compiler error: expected type/identifier node but found "
			<< A->nodeType() << "/" << B->nodeType() << endl;
	} else {
		idNode->type(typeNode);
		cout << "declare " << idNode->name() << " as type " << idNode->type() << endl; 
	}
}

statement ::= TYPE IDENTIFIER ASSIGNMENT expr SEMI. {
}

expr(A) ::= INT(B). {
    A = B;
}

expr(A) ::= FLOAT(B). {
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
expr(A) ::= expr(B) MOD expr(C). {
    A = new BinaryOpNode(MOD, B, C);
}

expr(A) ::= LPAREN expr(B) RPAREN. {
    A = B;
}
