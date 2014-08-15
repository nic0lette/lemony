#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

#include "astnode.h"

class ParserState {
public:
    BaseNode * result;
	int eval;
    ParserState() : result(0) {
    }
};

#endif // CALC_SCANNER_DEF_H_
