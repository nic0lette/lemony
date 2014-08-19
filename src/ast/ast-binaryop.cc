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
