#include "symboltable.h"

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