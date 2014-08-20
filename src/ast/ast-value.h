#ifndef AST_VALUE_H_
#define AST_VALUE_H_

#include <string>

#include "ast-base.h"
#include "ast-error.h"

class ValueNode : public BaseNode {

public:
	const char * nodeType() { return "value"; }

	virtual BaseNode * add(ValueNode * rhs);
	virtual BaseNode * sub(ValueNode * rhs);
	virtual BaseNode * mul(ValueNode * rhs);
	virtual BaseNode * div(ValueNode * rhs);
	virtual BaseNode * mod(ValueNode * rhs);	
};

#endif