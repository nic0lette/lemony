#include "ast-ident.h"
#include "../symboltable.h"

void IdentifierNode::type(LightweightTypeNode * type) {
	_type = type->itype();
}

string IdentifierNode::toString() {
	return _name;
}

BaseNode * IdentifierNode::eval() {
	IdentifierNode * c = SymbolTable::table()->lookup(_name);
	
	if (c == 0) {
		// First time being declared, do we have to type check it's value?
		if (_value != 0) {
			// Okay, there's a value, figure out what the value actually is
			BaseNode * b = _value->eval();
			
			// in order to be valid, this node can't just be a BaseNode
			// it *has* to be a ValueNode
			ValueNode * v = dynamic_cast<ValueNode *>(b);
			if (v == 0) {
				// Don't know what it is, but it isn't good
				return new ErrorNode("cannot assign value of type "
					+ b->type() + " to identifier " + _name
						+ " of type " + type());
			}
			
			// Okay, so we have a value node! Let's just... oh, let's check the
			// type
			if (v->itype() != _type) {
				// Nope
				return new ErrorNode("cannot assign value of type "
					+ v->type() + " to identifier " + _name
						+ " of type " + type());
			}
			
			// Perfect! save the value now that we've gone through all that work
			_value = v;
		}
		
		// Now that we've set the value (or not) install us into the symbol
		// table and return
		SymbolTable::table()->install(this);
		return new BaseNode();
	} else {
		return new ErrorNode("symbol already defined: " + _name
			+ " : defined as a " + c->type());
	}
}

void IdentifierNode::free() {
	if (_value != 0) {
		_value->free();
		delete _value;
	}
}