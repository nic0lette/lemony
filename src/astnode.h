#ifndef AST_NODES_H_
#define AST_NODES_H_

#include <iostream>

using namespace std;

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4

// Base class of all nodes in the tree
class BaseNode {
public:
	BaseNode() {};
	virtual ~BaseNode() {}
	
	virtual BaseNode * add(BaseNode * rhs);
	virtual BaseNode * sub(BaseNode * rhs);
	virtual BaseNode * mul(BaseNode * rhs);
	virtual BaseNode * div(BaseNode * rhs);
	virtual BaseNode * mod(BaseNode * rhs);
	
	virtual void printNode() { cout << "[BaseNode print]" << endl; }
	virtual const char * nodeType() { return "[BaseNode]"; }
	
	// Only needs to be defined by functions etc...
	virtual BaseNode * eval() { cout << "[Eval:Base]:" << nodeType() << endl; return this; };
	
	// Normally there's nothing to do for free (only non-leaf children need it)
	virtual void free() {};
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
	
	void printNode() {
		cout << "(";
		
		lhs->printNode();
		
		switch(op) {
			case ADD:
			cout << " + ";
			break;
			case SUB:
			cout << " - ";
			break;
			case MUL:
			cout << " * ";
			break;
			case DIV:
			cout << " / ";
			break;
			case MOD:
			cout << " %% ";
			break;
			default:
			cout << "IDEK" << endl;
		}
		
		rhs->printNode();

		cout << ")";
	}

	// Free the memory used only by the children, ours will be freed by our parent
	void free() {
		if (lhs) { lhs->free(); delete lhs; }
		if (rhs) { rhs->free(); delete rhs; }
	}
	
	BaseNode * eval() {
		switch(op) {
			case ADD: cout << "::eval +::"; break;
			case SUB: cout << "::eval -::"; break;
			case MUL: cout << "::eval *::"; break;
			case DIV: cout << "::eval /::"; break;
			case MOD: cout << "::eval %::"; break;
			default: return new ErrorNode("Internal error: unknown operator found in AST");
		}
		
		cout << lhs->nodeType() << " & " << rhs->nodeType() << endl;
		
		BaseNode * elhs = lhs->eval();
		BaseNode * erhs = rhs->eval();
		cout << "lhs: " << elhs->nodeType() << " rhs: " << rhs->nodeType() << " ";
		
		BaseNode * res;
		switch(op) {
			case ADD: res = elhs->add(erhs); break;
			case SUB: res = elhs->sub(erhs); break;
			case MUL: res = elhs->mul(erhs); break;
			case DIV: res = elhs->div(erhs); break;
			case MOD: res = elhs->mod(erhs); break;
			default: return new ErrorNode("Internal error: unknown operator found in AST");
		}
		cout << "Result type: " << res->nodeType() << endl;
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