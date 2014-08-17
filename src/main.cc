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
	
	// initialize state
	state.eval = 0;
	
    // scanner.scan return 0 when get EOF.
    while ((tokenID = scanner.scan(yylval)) != 0) {
        Parse(pParser, tokenID, yylval, &state);
		
		if (state.eval) {
			state.result->printNode();
			
			state.eval = 0;
			state.result = 0;
			
			/*
			 * Because we ate the token to eval the statement
			 * we have to, essentially, parse it again
			 */
	        Parse(pParser, tokenID, yylval, &state);
		}
    }

    Parse(pParser, tokenID, yylval, &state);
	if (state.result == 0) {
		cout << "Our result is null?" << endl;
	} else {
		state.result->printNode();
	}
	
	ParseFree(pParser, free);
    return 0;
}

