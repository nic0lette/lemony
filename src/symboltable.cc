#include "symboltable.h"
#include "ast.h"

// Static init
SymbolTable * SymbolTable::_table = 0;

// A new scope is actually simple. Create a new table, point at the current one
// and you're done
SymbolTable * SymbolTable::newScope() {
	SymbolTable::_table = new SymbolTable(SymbolTable::_table);
	return SymbolTable::_table;
}

IdentifierNode * SymbolTable::lookup(string symbol) {
	IdentifierNode * sym = _symbols[symbol];
	if (sym == 0 && _parent != 0) {
		return _parent->lookup(symbol);
	}
	return sym;
}

bool SymbolTable::install(IdentifierNode * sym) {
	IdentifierNode * curSym = _symbols[sym->name()];
	if (curSym != 0) {
		// Symbol exists (ie: duplicate declaration/definition)
		return false;
	}
	_symbols[sym->name()] = sym;
	return true;
}