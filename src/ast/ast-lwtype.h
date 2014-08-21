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
	int type() { return _type; }
	
	string toString();
	
	string nodeType() { return "lwtype"; }
};

#endif