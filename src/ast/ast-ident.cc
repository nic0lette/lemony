#include "ast-ident.h"

void IdentifierNode::type(LightweightTypeNode * type) {
	_type = type->type();
}

string IdentifierNode::toString() {
	return _name;
}