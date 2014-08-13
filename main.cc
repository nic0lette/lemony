#include <sstream>
#include <cassert>
#include <cstdlib>
#include "scanner.h"
#include "parser.c"

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
	
    // scanner.scan return 0 when get EOF.
    while ((tokenID = scanner.scan(yylval)) != 0) {
		
#if DEBUG		
		if (tokenID == TOKEN_INT) {
			printf("GET INT: %d\n", yylval.int_value);
		} else {
	        printf("GET TOKEN: %d (%c)\n", tokenID, yylval.int_value);
		}
#endif
		
        Parse(pParser, tokenID, yylval, &state);
		
		if (state.eval) {
			printf("RESULT: %d\n", state.result);
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
	printf("RESULT: %d\n", state.result);
	
	ParseFree(pParser, free);
    return 0;
}

