#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

typedef union {
    int int_value;
} YYSTYPE;

class ParserState {
public:
    YYSTYPE result;
	bool eval;
    ParserState() {}
};

#endif // CALC_SCANNER_DEF_H_
