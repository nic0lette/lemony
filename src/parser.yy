%token_prefix TOKEN_

%left ASSIGNMENT.
%left ADD SUB.
%left MUL DIV MOD.

%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <iostream>
#include "scanner.def.h"

	BaseNode * createVariable(BaseNode *& type, BaseNode *& id) {
		LightweightTypeNode * typeNode = dynamic_cast<LightweightTypeNode *>(type);
		ReferenceNode * refNode = dynamic_cast<ReferenceNode *>(id);
	
		if (typeNode != 0 || refNode != 0) {
			// Okay, the world is sane
			IdentifierNode * idNode = new IdentifierNode(refNode->name());
			idNode->type(typeNode);
		
			// This is why I call it a "lightweight" type node - it's job is over
			// (sorry little node)
			delete type;
			
			// And, actually since we're creating an IdentifierNode, we don't need the ref either
			delete id;
		
			// Send it back up
			return idNode;
		} else {
			cerr << "internal compiler error: expected type/identifier node but found "
				<< type->type() << "/" << id->type() << endl;
		
			// I don't even know... Make an error node?
			delete type;
			delete id;
		
			return new ErrorNode("How did you do that?");
		}
	}
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

statement(A) ::= TYPE(B) IDENTIFIER(C) SEMI. {
	A = createVariable(B, C);
}

statement(A) ::= TYPE(B) IDENTIFIER(C) ASSIGNMENT expr(D) SEMI. {
	BaseNode * pvar = createVariable(B, C);
	IdentifierNode * var = dynamic_cast<IdentifierNode *>(pvar);
	if (var != 0) {
		var->assign(D);
		A = var;
	} else {
		A = pvar;
	}
}

expr(A) ::= INT(B). {
    A = B;
}

expr(A) ::= FLOAT(B). {
    A = B;
}

expr(A) ::= IDENTIFIER(B). {
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

expr(A) ::= IDENTIFIER(B) ASSIGNMENT expr(C). {
	A = new BinaryOpNode(ASSIGN, B, C);
}