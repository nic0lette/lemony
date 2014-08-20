#ifndef AST_FLOAT_H_
#define AST_FLOAT_H_

#include <stdio.h>
#include <string>
#include <cstring>

#include "ast-base.h"
#include "ast-int.h"

using namespace std;

// Forward declare int
class IntNode;

class FloatNode : public ValueNode {
protected:
	static const int _type = REAL;
	
private:
	double _value;
	
public:
	FloatNode(double v) : _value(v) {}
	FloatNode(double v, int t) : _value(v) {
		if (t) BaseNode::setTemp();
	}
	
	const char * nodeType() { return "real"; }
	
	double getValue() { return _value; }
	
	/*
	 * Operators
	 */
	BaseNode * add(ValueNode * rhs);
	BaseNode * sub(ValueNode * rhs);
	BaseNode * mul(ValueNode * rhs);
	BaseNode * div(ValueNode * rhs);
	
	string toString() {
		char v[100]; // This is ridiculously huge >_>
		snprintf(v, 100, "%g", _value);
		
		if (strchr(v, '.') == 0) {
			strncat(v, ".0", 2);
		}
		return string(v);
	}
};

#endif