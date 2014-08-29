#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "scanner.h"
#include "parser.c"

using namespace std;

#define DEBUG 0

int main() {
    YYSTYPE yylval;
    Scanner scanner(&std::cin);
    void * pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
	
	// initialize state
	state.eval = 0;
	
    // because do...while() loops are evil for some reason... idek
	while (true) {
		tokenID = scanner.scan(yylval);
		Parse(pParser, tokenID, yylval, &state);
		
		// Next statement?
		if (state.eval) {
			// Mark end of parsed block
			std::cout << "------------------------------" << std::endl;
			
			// Reparse that last token
			state.eval = false;
			Parse(pParser, tokenID, yylval, &state);
		}

		// end of the input stream?
		if (tokenID == 0) {
			break;
		}
	}
	
	ParseFree(pParser, free);
    return 0;
}

