#ifndef AST_IDENTIFIER_H_
#define AST_IDENTIFIER_H_

#include "ast-types.h"
#include "ast-base.h"
#include "ast-lwtype.h"
#include "ast-value.h"
#include "ast-error.h"

using namespace std;

// Base class of all nodes in the tree
class IdentifierNode : public BaseNode {
protected:
	string _name;
	int _type;
	BaseNode * _value;
	
public:
	IdentifierNode(string name) : _name(name) {}
	string name() { return _name; }
	string type() { return TYPE_NAMES[_type]; }
	
	void type(LightweightTypeNode *);
	
	void assign(BaseNode * value) { _value = value; }
	
	string toString();
	string nodeType() { return "identifier"; }
	
	BaseNode * eval();
	
	// Normally there's nothing to do for free (only non-leaf children need it)
	void free();
};

#endif