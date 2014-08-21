#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <string>
#include <map>

#include "ast.h"

class SymbolTable {
private:
	std::map<string, IdentifierNode *> _symbols;
	SymbolTable * _parent;
	
public:
	SymbolTable() : _parent(0) {}
	SymbolTable(SymbolTable * parent) : _parent(parent) {}
	
	// Find the given symbol
	IdentifierNode * lookup(string);
	
	// Install a new symbol in the current table
	bool install(IdentifierNode *);
};

#endif