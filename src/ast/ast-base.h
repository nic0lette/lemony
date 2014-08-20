#ifndef AST_NODES_H_
#define AST_NODES_H_

#include <iostream>

#include "ast-types.h"

using namespace std;

// Base class of all nodes in the tree
class BaseNode {
protected:
	static const int _type = VOID;
	
	// Is this node a temporary node (partial evaluation result)
	int _temp;
	void setTemp() { _temp = 1; }
	
public:
	BaseNode() : _temp(0) {};
	virtual ~BaseNode() {}
	
	// Just returns whether a node is a temp node or not
	inline int isTemp() { return _temp; }
	
	virtual string toString();
	
	virtual const char * nodeType() { return "base"; }
	
	// Only needs to be defined by functions etc...
	virtual BaseNode * eval() { return this; };
	
	// Normally there's nothing to do for free (only non-leaf children need it)
	virtual void free() {};
};

#endif