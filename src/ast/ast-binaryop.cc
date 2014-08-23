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
	switch(op) {
		case ADD: // fall through
		case SUB: // fall through
		case MUL: // fall through
		case DIV: // fall through
		case MOD: return mathEval();
		case ASSIGN: return assignEval();
		default: return new ErrorNode("Internal error: unknown operator found in AST");
	}
}

BaseNode * BinaryOpNode::assignEval() {
	// For variable assignment
	BaseNode * erhs = rhs->eval();
	BaseNode * res;
	
	// At this point the lhs should be an identifier and the rhs a value
	ReferenceNode * idRef = dynamic_cast<ReferenceNode *>(lhs);
	ValueNode * val = dynamic_cast<ValueNode *>(erhs);
	
	if (idRef == 0) {
		// Did we already get an error?
		ErrorNode * err = dynamic_cast<ErrorNode *>(idRef);
		if (err != 0) {
			// Okay, they already have an error, so don't make a new one
			if (erhs->isTemp()) delete erhs;
			return err;
		} else {
			res = new ErrorNode(erhs->type() + " is not a valid lval");
		}
	}
	if (val == 0) {
		// Did we already get an error?
		ErrorNode * err = dynamic_cast<ErrorNode *>(idRef);
		if (err != 0) {
			// Okay, they already have an error, so don't make a new one
			return err;
		} else {
			res = new ErrorNode(erhs->type() + " is not a valid lval");
		}
	}
	
	// Everything okay?
	if (idRef != 0 && val != 0) {
		// Okay, so now that we have the reference to the real identifier, let's get the identifier
		IdentifierNode * id = idRef->get();
		
		// Check that it worked
		if (id == 0) {
			if (erhs->isTemp()) delete erhs;
			return new ErrorNode("failed to retrive identifier " + idRef->name());
		}
		
		// Ensure the types match		
		if (id->itype() != val->itype()) {
			// Type mismatch
			res = new ErrorNode("cannot assign value of type " + val->type() + " identifier of type "
				+ id->type() + " (" + id->name() + ")");
		} else {
			// Yay! Do the assignment and return the value we have
			id->assign(val);
			res = val;
		}
	}
	
	// There's no way the lhs will need to be deleted unless the parser blew up
	// since it *must* be either an IdentifierNode or an ErrorNode, neither of which
	// we'll want to delete
	return res;
}

BaseNode * BinaryOpNode::mathEval() {
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
