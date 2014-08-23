#include "ast-ref.h"
#include "../symboltable.h"

int ReferenceNode::itype() {
	// To eval, we first need to get the symbol
	IdentifierNode * sym = SymbolTable::table()->lookup(_id);
	
	// Is there even such a symbol?
	if (sym == 0) {
		return VOID;
	}
	
	// Their type is our type
	return sym->itype();
}

BaseNode * ReferenceNode::eval() {
	// To eval, we first need to get the symbol
	IdentifierNode * sym = SymbolTable::table()->lookup(_id);
	
	// Is there even such a symbol?
	if (sym == 0) {
		return new ErrorNode("no symbol '" + _id + "' defined in the current scope.");
	}
	
	// Does it have a value?
	BaseNode * v = sym->value();
	if (v == 0) {
		return new ErrorNode("attempt to dereference unassigned variable: " + _id);
	}
	
	// Perfect! return the value
	return v;
}

IdentifierNode * ReferenceNode::get() {
	// To eval, we first need to get the symbol
	IdentifierNode * sym = SymbolTable::table()->lookup(_id);
	
	// Is there even such a symbol?
	if (sym == 0) {
		return 0;
	}
	
	// Does it have a value?
	BaseNode * v = sym->value();
	if (v == 0) {
		return 0;
	}
	
	// Perfect! Return the symbol
	return sym;
}