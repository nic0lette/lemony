#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "scanner.h"
#include "parser.c"

using namespace std;

#define DEBUG 0

int main() {
    BaseNode * yylval;
    Scanner scanner(&std::cin);
    void * pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
	
    // scanner.scan return 0 when get EOF.
    while ((tokenID = scanner.scan(yylval)) != 0) {
		// Is there an old symbol to discard?
		if (state.prevSym != 0) {
			delete [] state.prevSym;
		}
		
		// Set state for the parser
		state.line = scanner.lineno();
		state.prevSym = state.curSym;
		state.curSym = scanner.currentToken();
		
		// Parse the token
        Parse(pParser, tokenID, yylval, &state);
		
		if (state.astRoot != 0) {
			if (!state.parseError)
				cout << "Result: " << state.astRoot->eval()->toString() << endl;
			
			// Reset and continue
			state.reset();
			
			/*
			 * Because we ate the token to eval the statement
			 * we have to, essentially, parse it again
			 */
	        Parse(pParser, tokenID, yylval, &state);
		}
    }

    Parse(pParser, tokenID, yylval, &state);
	if (state.astRoot == 0) {
		if (!state.parseError)
			cout << "Result: " << state.astRoot->eval()->toString() << endl;
	}
	
	ParseFree(pParser, free);
    return 0;
}

