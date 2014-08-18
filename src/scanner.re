#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "scanner.def.h"
#include "parser.h"

class Scanner {
private:
	// iostream sucks. very slow.
	std::istream *ifs;
 
	// buffer memory
	char* m_buffer;
    
	// current position
	char* m_cursor;
	char* m_limit;
	char* m_token;
	char* m_marker;
	int m_buffer_size;
	
	// State for the parser
	int m_lineno;
	char * m_current_token;
 
public:

    Scanner( std::istream *ifs_, int init_size = 1024 )
        : m_buffer(0)
        , m_cursor(0)
        , m_limit(0)
        , m_token(0)
        , m_marker(0)
        , m_buffer_size(init_size)
        , m_lineno(1)
		, m_current_token(0)
    {
        m_buffer = new char[m_buffer_size];
        m_cursor = m_limit = m_token = m_marker = m_buffer;
        ifs = ifs_;
    }
 
    ~Scanner() {
        delete [] m_buffer;
    }
 
    bool fill(int n) {
 
        // is eof?
        if (ifs->eof()) {
            if ((m_limit-m_cursor) <= 0) {
                return false;
            }
        }
 
        int restSize = m_limit-m_token;
        if (restSize+n >= m_buffer_size) {
            // extend buffer
            m_buffer_size *= 2;
            char* newBuffer = new char[m_buffer_size];
            for (int i = 0; i < restSize; ++i) { // memcpy
                *(newBuffer + i) = *(m_token + i);
            }
            m_cursor = newBuffer + (m_cursor-m_token);
            m_token = newBuffer;
            m_limit = newBuffer + restSize;
 
            delete [] m_buffer;
            m_buffer = newBuffer;
        } else {
            // move remained data to head.
            for (int i = 0; i < restSize; ++i) {
                *(m_buffer + i) = *(m_token + i);
            }
            m_cursor = m_buffer + (m_cursor-m_token);
            m_token = m_buffer;
            m_limit = m_buffer+restSize;
        }
 
        // fill to buffer
        int read_size = m_buffer_size - restSize;
        ifs->read(m_limit, read_size);
        m_limit += ifs->gcount();
 
        return true;
    }
 
	char * token() {
		char * a = new char[length() + 1];
		a[length()] = '\0';
		memcpy(a, m_token, length());
		
		// Save the token before returning
		m_current_token = a;
		return a;
	}
    
	int length() {
        return (m_cursor-m_token);
    }
    
    void increment_line_number() {
        m_lineno++;
    }

	int lineno() {
        return m_lineno;
    }
	
	int setAndReturn(char token, int ttype) {
		char * t = new char[2];
		t[0] = token;
		t[1] = '\0';
		m_current_token = t;
		
		return ttype;
	}
	
	char * currentToken() {
		return m_current_token;
	}
	
	IntNode * intToken() {
		// Convert the string token to a char[]
		char * t = this->token();
		
		// Parse the hex value
        int value = (int)strtol(t, NULL, 0);
		
		// Done! (t will be freed elsewhere)
		return new IntNode(value);
	}
	
    int scan(BaseNode * & yylval) {
		std:
        m_token = m_cursor;
		
    /*!re2c
        re2c:define:YYCTYPE = "char";
        re2c:define:YYCURSOR = m_cursor;
        re2c:define:YYMARKER = m_marker;
        re2c:define:YYLIMIT = m_limit;
        re2c:define:YYFILL:naked = 1;
        re2c:define:YYFILL@len = #;
        re2c:define:YYFILL = "if (!fill(#)) { return 0; }";
        re2c:yyfill:enable = 1;
        re2c:indent:top = 2;
        re2c:indent:string="    ";

        INTEGER				= [0][0-7]*|[1-9][0-9]*|[0][x][0-9,a-f,A-F]*;
        WS					= [ \t\f];
		NEW_LINE			= [\n][\r]|[\r][\n]|[\n];
        ANY_CHARACTER		= [^];

        INTEGER { yylval = intToken(); return TOKEN_INT; }
        "+" { return setAndReturn('+', TOKEN_ADD); }
        "-" { return setAndReturn('-', TOKEN_SUB); }
        "*" { return setAndReturn('*', TOKEN_MUL); }
        "/" { return setAndReturn('/', TOKEN_DIV); }
		"%" { return setAndReturn('\%', TOKEN_MOD); }
        "(" { return setAndReturn('(', TOKEN_LPAREN); }
        ")" { return setAndReturn(')', TOKEN_RPAREN); }
		";" { return setAndReturn(';', TOKEN_SEMI); }
		NEW_LINE {
			increment_line_number();
			goto std;
		}
        WS {
            goto std;
        }
        ANY_CHARACTER {
            printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
            goto std;
        }

    */

    }
};

#endif // CALC_SCANNER_H_
