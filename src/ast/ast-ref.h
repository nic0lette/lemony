#ifndef AST_REF_H_
#define AST_REF_H_

#include <string>

#include "ast-types.h"
#include "ast-base.h"
#include "ast-value.h"
#include "ast-ident.h"

class ReferenceNode : public BaseNode {
private:
	// Name of the identifier we're referencing
	string _id;
	
public:
	ReferenceNode(string id) : _id(id) {}
	string name() { return _id; }

	int itype();
	string type() { return TYPE_NAMES[itype()]; }
	
	BaseNode * eval();
	IdentifierNode * get();
};

#endif