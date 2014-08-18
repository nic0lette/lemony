#ifndef AST_NODES_H_
#define AST_NODES_H_

#include <iostream>

using namespace std;

// Operators
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4

// Types
#define VOID 0
#define INT 1
#define REAL 2
#define BOOL 3
#define STRING 4

// Base class of all nodes in the tree
class BaseNode {
protected:
	static const int _type = VOID;
	
	// Is this node a temporary node (partial evaluation result)
	int _temp;
	void setTemp() { _temp = 1; }
	
public:
	BaseNode() : _temp(0) {};
	virtual ~BaseNode() {}
	
	virtual BaseNode * add(BaseNode * rhs);
	virtual BaseNode * sub(BaseNode * rhs);
	virtual BaseNode * mul(BaseNode * rhs);
	virtual BaseNode * div(BaseNode * rhs);
	virtual BaseNode * mod(BaseNode * rhs);
	
	virtual string toString() {
		char s[100];
		snprintf(s, 100, "[BaseNode:%s]", nodeType());
		return string(s);
	}
	virtual const char * nodeType() { return "[BaseNode]"; }
	
	// Only needs to be defined by functions etc...
	virtual BaseNode * eval() { return this; };
	
	// Normally there's nothing to do for free (only non-leaf children need it)
	virtual void free() {};
	
	// Just returns whether a node is a temp node or not
	int isTemp() { return _temp; }
};

// Base error node
class ErrorNode : public BaseNode {
private:
	std::string _msg;
public:
	ErrorNode(std::string msg="Unknown error") : _msg(msg) {};
	const char * nodeType() { return "[ErrorNode]"; }
	
	std::string getMessage() { return _msg; }

	void printNode() { cerr << "error(" << _msg << ")" << endl; }
};

class BinaryOpNode : public BaseNode {
public:
	int op;
	BaseNode * lhs;
	BaseNode * rhs;
	
	BinaryOpNode(int op, BaseNode * lhs, BaseNode * rhs) : op(op), lhs(lhs), rhs(rhs) {}
	const char * nodeType() { return "[BinaryOpNode]"; }
	
	string toString() {
		switch(op) {
			case ADD: return string("+");
			case SUB: return string("-");
			case MUL: return string("*");
			case DIV: return string("/");
			case MOD: return string("%");
			default:
			return string("[BOO:Unknown]");
		}
	}

	// Free the memory used only by the children, ours will be freed by our parent
	void free() {
		if (lhs) { lhs->free(); delete lhs; }
		if (rhs) { rhs->free(); delete rhs; }
	}
	
	BaseNode * eval() {
		// Evaluate the two operands
		BaseNode * elhs = lhs->eval();
		BaseNode * erhs = rhs->eval();
		BaseNode * res;

		switch(op) {
			case ADD: res = elhs->add(erhs); break;
			case SUB: res = elhs->sub(erhs); break;
			case MUL: res = elhs->mul(erhs); break;
			case DIV: res = elhs->div(erhs); break;
			case MOD: res = elhs->mod(erhs); break;
			default: res = new ErrorNode("Internal error: unknown operator found in AST");
		}
		
		// Free temp results
		if (elhs->isTemp()) delete elhs;
		if (erhs->isTemp()) delete erhs;
		
		// Done
		return res;
	}
};

/*
 * Include other node types
 */
#include "typenodes.h"

/*
 * Base type default implementations
 * (Not implemented)
 */
BaseNode * BaseNode::add(BaseNode * rhs) { return new ErrorNode("not implemented"); }
BaseNode * BaseNode::sub(BaseNode * rhs) { return new ErrorNode("not implemented"); }
BaseNode * BaseNode::mul(BaseNode * rhs) { return new ErrorNode("not implemented"); }
BaseNode * BaseNode::div(BaseNode * rhs) { return new ErrorNode("not implemented"); }
BaseNode * BaseNode::mod(BaseNode * rhs) { return new ErrorNode("not implemented"); }

#endif