#include "ast-binaryop.h"

string BinaryOpNode::toString() {
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
void BinaryOpNode::free() {
	if (lhs) { lhs->free(); delete lhs; }
	if (rhs) { rhs->free(); delete rhs; }
}

BaseNode * BinaryOpNode::eval() {
	// Evaluate the two operands
	BaseNode * elhs = lhs->eval();
	BaseNode * erhs = rhs->eval();
	
	// At this point the lhs and rhs of the operator should be ValueNodes
	ValueNode * vlhs = dynamic_cast<ValueNode *>(elhs);
	ValueNode * vrhs = dynamic_cast<ValueNode *>(erhs);
	
	// This shouldn't be able to be broken unless our parser messed up
	if (vlhs == 0 || vrhs == 0) {
		char msg[255];
		snprintf(msg, 255, "internal compiler error: operands for %c are not values",
			OP_NAMES[op]);
		return new ErrorNode(msg);
	}
	
	BaseNode * res;

	switch(op) {
		case ADD: res = vlhs->add(vrhs); break;
		case SUB: res = vlhs->sub(vrhs); break;
		case MUL: res = vlhs->mul(vrhs); break;
		case DIV: res = vlhs->div(vrhs); break;
		case MOD: res = vlhs->mod(vrhs); break;
		default: res = new ErrorNode("Internal error: unknown operator found in AST");
	}
	
	// Free temp results
	if (elhs->isTemp()) delete elhs;
	if (erhs->isTemp()) delete erhs;
	
	// Done
	return res;
}
