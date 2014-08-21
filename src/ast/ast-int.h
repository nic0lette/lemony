#ifndef AST_INT_H_
#define AST_INT_H_

#include <stdio.h>
#include <string>
#include <cstring>

#include "ast-base.h"
#include "ast-value.h"
#include "ast-float.h"

using namespace std;

class IntNode : public ValueNode {
protected:
	
private:
	long long _value;
	
public:
	IntNode(long long v) : _value(v) {}
	IntNode(long long v, int t) : _value(v) {
		if (t) BaseNode::setTemp();
	}
	
	int type() { return INT; }
	string nodeType() { return "int"; }
	
	long long getValue() { return _value; }
	
	/*
	 * Operators
	 */
	BaseNode * add(ValueNode * rhs);
	BaseNode * sub(ValueNode * rhs);
	BaseNode * mul(ValueNode * rhs);
	BaseNode * div(ValueNode * rhs);
	BaseNode * mod(ValueNode * rhs);
	
	string toString() {
		char v[100]; // This is ridiculously huge >_>
		snprintf(v, 100, "%lld", _value);
		return string(v);
	}
};

#endif