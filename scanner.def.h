#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

typedef union {
    int int_value;
} YYSTYPE;

class ParserState {
public:
    int result;
	int eval;
    ParserState() : result(0) {
    }
};

#endif // CALC_SCANNER_DEF_H_
