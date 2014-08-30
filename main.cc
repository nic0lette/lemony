#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <cstdlib>
#include "scanner.h"
#include "parser.c"

#define DEBUG 0

// Basically, let's convert a (likely) file based istream to a stringstream based one
std::stringstream * sstream(std::istream * in) {
	// We need it to be a pointer to a stream because the copy constructor is private
	// ... seriously.
	std::stringstream * str = new std::stringstream();
	
	// Copy the istream into our stringstream
	copy(std::istreambuf_iterator<char>(*in),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(*str));
		
	// Because our language needs to have a newline at the end, just... add one (just in case)
	// This kind of bothers me, actually... there should be a way to do this with lemon =/
	str->put('\n');
	
	return str;
}

// Let's create a string stream!
int main() {
    YYSTYPE yylval;

	// Let's convert from stdin (boo!) to our own stream (yay!)
	std::iostream * stream = sstream(&std::cin);
	Scanner scanner(stream);
	
	// Let's parse!
    void * pParser = ParseAlloc(malloc);
    int tokenID;

    ParserState state;
	
	// initialize state
	state.eval = 0;
	
	do {
		// Get the next token
		tokenID = scanner.scan(yylval);
		
		// Parse the token		
		Parse(pParser, tokenID, yylval, &state);
		
		// Done with this statement?
		if (state.eval) {
			// Yup! Statement complete
			state.eval = false;
			
			// Only reparse the token if it wasn't EOF?
			if (tokenID != 0) {
				Parse(pParser, tokenID, yylval, &state);
			}
		}
	} while (tokenID != 0);
	
	// And cleanup everything
	ParseFree(pParser, free);
	delete stream;
	
    return 0;
}

