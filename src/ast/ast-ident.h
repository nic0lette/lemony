#ifndef AST_IDENTIFIER_H_
#define AST_IDENTIFIER_H_

#include "ast-types.h"
#include "ast-base.h"
#include "ast-lwtype.h"

using namespace std;

// Base class of all nodes in the tree
class IdentifierNode : public BaseNode {
protected:
	string _name;
	int _type;
	
public:
	IdentifierNode(string name) : _name(name) {}
	string name() { return _name; }
	string type() { return TYPE_NAMES[_type]; }
	
	void type(LightweightTypeNode *);
	
	string toString();
	string nodeType() { return "identifier"; }
};

#endif