#ifndef TYPE_NODES_H_
#define TYPE_NODES_H_

#include <string>

using namespace std;

class IntNode : public BaseNode {
private:
	long long _value;
	
public:
	IntNode(long long v) : _value(v) {}
	const char * nodeType() { return "[IntNode]"; }
	
	long long getValue() { return _value; }
	
	/*
	 * Operators
	 */
	IntNode * add(IntNode * rhs) { cout << "Int+" << endl; return new IntNode(_value + rhs->getValue()); }
	IntNode * sub(IntNode * rhs) { cout << "Int-" << endl; return new IntNode(_value - rhs->getValue()); }
	IntNode * mul(IntNode * rhs) { cout << "Int*" << endl; return new IntNode(_value * rhs->getValue()); }
	IntNode * div(IntNode * rhs) { cout << "Int/" << endl; return new IntNode(_value / rhs->getValue()); }
	IntNode * mod(IntNode * rhs) { cout << "Int%%" << endl; return new IntNode(_value % rhs->getValue()); }
	
	void printNode() { cout << _value << "i"; }
};

#endif