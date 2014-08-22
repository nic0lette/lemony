#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <string>
#include <map>

// Because of the tight relationship between this and both IdentifierNode
// (which is a BaseNode) and BaseNode's inclusion of this class, we need
// to just declare the class here and hope for the best
class IdentifierNode;

class SymbolTable {
private:
	std::map<std::string, IdentifierNode *> _symbols;
	SymbolTable * _parent;

	// Since it's a static thing, no reason for other people to construct it
	SymbolTable() : _parent(0) {}
	SymbolTable(SymbolTable * parent) : _parent(parent) {}
	
	// The actual current symbol table
	static SymbolTable * _table;
	
public:
	// Creates a symbol table to accompany a new scope
	static SymbolTable * newScope();
	
	// Get the symbol table for the current scope
	static SymbolTable * table() { return _table; }
		
	// Find the given symbol
	IdentifierNode * lookup(std::string);
	
	// Install a new symbol in the current table (true=install succeeded)
	bool install(IdentifierNode *);
};

#endif