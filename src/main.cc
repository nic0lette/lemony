#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

#include "ast.h"
#include "scanner.h"
#include "parser.c"

using namespace std;

#define DEBUG 0

void printResult(BaseNode * res) {
	BaseNode * r = res->eval();
	ValueNode * v = dynamic_cast<ValueNode *>(r);
	if (v != 0) {
		cout << "Result: " << v->toString() << endl;
	} else {
		cout << r->toString() << endl;
	}
}

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
			if (!state.parseError) {
				printResult(state.astRoot);
			}
			
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
	if (state.astRoot != 0) {
		if (!state.parseError) {
			printResult(state.astRoot);
		}
	}
	
	ParseFree(pParser, free);
    return 0;
}

