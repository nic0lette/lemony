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
	int m_lineno;
 
public:

    void increment_line_number() {
        m_lineno++;
    }

    Scanner( std::istream *ifs_, int init_size = 1024 )
        : m_buffer(0)
        , m_cursor(0)
        , m_limit(0)
        , m_token(0)
        , m_marker(0)
        , m_buffer_size(init_size)
        , m_lineno(1)
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
 
    std::string text() {
        return std::string(m_token, m_token + length());
    }
	
	int length() {
        return (m_cursor-m_token);
    }
    
	int lineno() {
        return m_lineno;
    }
	
	int intToken() {
		// Parse the token value
        int value = (int)strtol(text().c_str(), NULL, 0);
		
		// Done!
		return value;
	}
	
    int scan(YYSTYPE& yylval) {
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

		FUNC				= "f";
		DEF					= "def";
		SYM					= [_,A-Z,a-z]*;
        INTEGER				= [0][0-7]*|[1-9][0-9]*|[0][x][0-9,a-f,A-F]*;
		NEWLINE				= [\n];
        WS					= [ \r\t\f];
        ANY_CHARACTER		= [^];
		
		// keywords
		DEF { return TOKEN_DEF; }
		FUNC { return TOKEN_FUNCTION; }
		
		// Symbol
		SYM {
			return TOKEN_SYM;
		}
		
		// Values
        INTEGER {
			yylval.int_value = intToken();
			return TOKEN_INT;
		}
		
		// Operators
        "+" { return TOKEN_ADD; }
        "-" { return TOKEN_SUB; }
        "*" { return TOKEN_MUL; }
        "/" { return TOKEN_DIV; }
        "(" { return TOKEN_LPAREN; }
        ")" { return TOKEN_RPAREN; }
		"->" { return TOKEN_MAPS; }
		":" { return TOKEN_COLON; }
		"," { return TOKEN_COMMA; }
		
		// Misc.
		NEWLINE { return TOKEN_NEWLINE; }
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
