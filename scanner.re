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

    Scanner( std::istream *ifs_, int init_size=1024 )
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
            for (int i=0; i<restSize; ++i) { // memcpy
                *(newBuffer+i) = *(m_token+i);
            }
            m_cursor = newBuffer + (m_cursor-m_token);
            m_token = newBuffer;
            m_limit = newBuffer + restSize;
 
            delete [] m_buffer;
            m_buffer = newBuffer;
        } else {
            // move remained data to head.
            for (int i=0; i<restSize; ++i) { //memmove( m_buffer, m_token, (restSize)*sizeof(char) );
                *(m_buffer+i) = *(m_token+i);
            }
            m_cursor = m_buffer + (m_cursor-m_token);
            m_token = m_buffer;
            m_limit = m_buffer+restSize;
        }
 
        // fill to buffer
        int read_size = m_buffer_size - restSize;
        ifs->read( m_limit, read_size );
        m_limit += ifs->gcount();
 
        return true;
    }
 
    std::string text() {
        return std::string( m_token, m_token+length() );
    }
	char * textAsChar() {
		char * a = new char[length() + 1];
		a[length()]='\0';
		memcpy(a, m_token, length());
		return a;
	}
    int length() {
        return (m_cursor-m_token);
    }
    int lineno() {
        return m_lineno;
    }
	int intToken() {
		// Convert the string token to a char[]
		char * token = this->textAsChar();
		
		// Parse the hex value
        int value = (int)strtol(token, NULL, 0);
		
		// Free the memory and return the token
		delete [] token;
		
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

        INTEGER_OCT            = [0][0-7]*;
        INTEGER_DEC            = [1-9][0-9]*;
        INTEGER_HEX            = [0][x][0-9,a-f,A-F]*;
        WS                     = [ \r\n\t\f];
        ANY_CHARACTER          = [^];

        INTEGER_OCT { yylval.int_value = this->intToken(); return TOKEN_INT; }
        INTEGER_DEC { yylval.int_value = this->intToken(); return TOKEN_INT; }
        INTEGER_HEX { yylval.int_value = this->intToken(); return TOKEN_INT; }
        "+" { yylval.int_value = '+'; return TOKEN_ADD; }
        "-" { yylval.int_value = '-'; return TOKEN_SUB; }
        "*" { yylval.int_value = '*'; return TOKEN_MUL; }
        "/" { yylval.int_value = '/'; return TOKEN_DIV; }
        "(" { yylval.int_value = '('; return TOKEN_LPAREN; }
        ")" { yylval.int_value = ')'; return TOKEN_RPAREN; }
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
