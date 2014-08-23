#ifndef AST_LW_TYPE_H_
#define AST_LW_TYPE_H_

#include "ast-base.h"

using namespace std;

// Base class of all nodes in the tree
class LightweightTypeNode : public BaseNode {
protected:
	int _type;
	
public:
	LightweightTypeNode(string);
	string type() { return "lwtype"; }
	int itype() { return _type; }
	
	string toString();
};

#endif