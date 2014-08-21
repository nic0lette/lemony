#ifndef AST_BINARY_OP_H_
#define AST_BINARY_OP_H_

#include <string>

#include "ast-base.h"
#include "ast-value.h"
#include "ast-error.h"

class BinaryOpNode : public BaseNode {
public:
	int op;
	BaseNode * lhs;
	BaseNode * rhs;
	
	BinaryOpNode(int op, BaseNode * lhs, BaseNode * rhs) : op(op), lhs(lhs), rhs(rhs) {}
	string nodeType() { return "[BinaryOpNode]"; }
	
	string toString();
	
	// Free the memory used only by the children, ours will be freed by our parent
	void free();
	
	// Evaluate this node
	BaseNode * eval();
};

#endif