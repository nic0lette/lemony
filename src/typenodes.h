#ifndef TYPE_NODES_H_
#define TYPE_NODES_H_

#include <stdio.h>
#include <string>
#include <cstring>

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

class FloatNode : public BaseNode {
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
	BaseNode * add(BaseNode * rhs);
	BaseNode * sub(BaseNode * rhs);
	BaseNode * mul(BaseNode * rhs);
	BaseNode * div(BaseNode * rhs);
	
	string toString() {
		char v[100]; // This is ridiculously huge >_>
		snprintf(v, 100, "%g", _value);
		
		if (strchr(v, '.') == 0) {
			strncat(v, ".0", 2);
		}
		return string(v);
	}
};

// Number type operator definitions
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	return BaseNode::f(rhs);

	BaseNode * IntNode::add(BaseNode * rhs) { OP(+, add) }
	BaseNode * IntNode::sub(BaseNode * rhs) { OP(-, add) }
	BaseNode * IntNode::mul(BaseNode * rhs) { OP(*, add) }
	BaseNode * IntNode::div(BaseNode * rhs) { OP(/, add) }
#undef OP

// Int only rules
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	return BaseNode::f(rhs);
	
	BaseNode * IntNode::mod(BaseNode * rhs) { OP(%, add) }
#undef OP	

#define OP(op,f) \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new FloatNode(_value op rhsi->getValue(), 1); \
	return BaseNode::f(rhs);


	BaseNode * FloatNode::add(BaseNode * rhs) { OP(+, add) }
	BaseNode * FloatNode::sub(BaseNode * rhs) { OP(-, add) }
	BaseNode * FloatNode::mul(BaseNode * rhs) { OP(*, add) }
	BaseNode * FloatNode::div(BaseNode * rhs) { OP(/, add) }
#undef OP


#endif