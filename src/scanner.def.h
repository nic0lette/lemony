#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

// Include the nodes that build the AST
#include "astnode.h"

// set the type for lemon tokens
#define YYSTYPE BaseNode *

class ParserState {
public:
	// The root of the Abstract Symbol Tree
    BaseNode * astRoot;
	
	// Current symbol being parsed
	char * curSym;
	
	// Token just processed
	char * prevSym;
	
	// Location in the source
	int line;
	
	// Was there an error
	int parseError;

	// Default constructor
    ParserState() : astRoot(0), curSym(0), prevSym(0), line(0), parseError(0) {
    }
	
	void reset() {
		// Get rid of the old AST if there is one
		if (astRoot != 0) {
			astRoot->free();
			delete astRoot;
		}
		
		astRoot = 0;
		curSym = 0;
		prevSym = 0;
		line = 0;
		parseError = 0;
	}
};

#endif // CALC_SCANNER_DEF_H_
