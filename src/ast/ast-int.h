#ifndef AST_INT_H_
#define AST_INT_H_

#include <stdio.h>
#include <string>
#include <cstring>

#include "ast-base.h"
#include "ast-float.h"

using namespace std;

class IntNode : public BaseNode {
protected:
	static const int _type = INT;
	
private:
	long long _value;
	
public:
	IntNode(long long v) : _value(v) {}
	IntNode(long long v, int t) : _value(v) {
		if (t) BaseNode::setTemp();
	}
	
	const char * nodeType() { return "int"; }
	
	long long getValue() { return _value; }
	
	/*
	 * Operators
	 */
	BaseNode * add(BaseNode * rhs);
	BaseNode * sub(BaseNode * rhs);
	BaseNode * mul(BaseNode * rhs);
	BaseNode * div(BaseNode * rhs);
	BaseNode * mod(BaseNode * rhs);
	
	string toString() {
		char v[100]; // This is ridiculously huge >_>
		snprintf(v, 100, "%lld", _value);
		return string(v);
	}
};

#endif