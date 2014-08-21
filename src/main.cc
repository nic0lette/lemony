#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

#include "ast.h"
#include "scanner.h"
#include "parser.c"

#include "symboltable.h"

using namespace std;

#define DEBUG 0

/*
 * GLOBALS
 */
SymbolTable globalVars = SymbolTable();
std::vector<BaseNode *> program = std::vector<BaseNode *>();

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
		// Set state for the parser
		state.line = scanner.lineno();
		state.prevSym = state.curSym;
		state.curSym = scanner.currentToken();
		
		// Parse the token
		Parse(pParser, tokenID, yylval, &state);
		
		if (state.astRoot != 0) {
			if (!state.parseError) {
				program.push_back(state.astRoot);
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
	
	// Add the final bit to the program
	Parse(pParser, tokenID, yylval, &state);
	if (state.astRoot != 0) {
		if (!state.parseError) {
			program.push_back(state.astRoot);
		}
	}
	
	// Done with the parser
	ParseFree(pParser, free);
	
	// Execute the program
	for (std::vector<BaseNode *>::iterator statement = program.begin();
		statement != program.end();
		++statement) {
			printResult(*statement);
	}
	
	// Now that we're done, free all of that memory (just to be polite)
	// (I mean, we're done, so the OS will do it anyway)
	// (But that isn't polite)
	for (std::vector<BaseNode *>::iterator statement = program.begin();
		statement != program.end();
		++statement) {
			(*statement)->free();
			delete (*statement);
	}
	
	// Done!
    return 0;
}

