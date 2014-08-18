#ifndef TYPE_NODES_H_
#define TYPE_NODES_H_

#include <stdio.h>
#include <string>

using namespace std;

#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->_value, 1); \
	return BaseNode::f(rhs);

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
	
	const char * nodeType() { return "[IntNode]"; }
	
	long long getValue() { return _value; }
	
	/*
	 * Operators
	 */
	BaseNode * add(BaseNode * rhs) { OP(+, add) }
	BaseNode * sub(BaseNode * rhs) { OP(-, add) }
	BaseNode * mul(BaseNode * rhs) { OP(*, add) }
	BaseNode * div(BaseNode * rhs) { OP(/, add) }
	BaseNode * mod(BaseNode * rhs) { OP(%, add) }
	
	string toString() {
		char v[100]; // This is ridiculously huge >_>
		snprintf(v, 100, "%lld", _value);
		return string(v);
	}
};

#undef OP

#endif