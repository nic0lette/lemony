#include "ast-ident.h"
#include "../symboltable.h"

void IdentifierNode::type(LightweightTypeNode * type) {
	_type = type->type();
}

string IdentifierNode::toString() {
	return _name;
}

BaseNode * IdentifierNode::eval() {
	if (SymbolTable::table()->install(this)) {
		return new BaseNode();
	} else {
		IdentifierNode * c = SymbolTable::table()->lookup(_name);
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