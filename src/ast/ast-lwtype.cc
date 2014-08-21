#include "ast-lwtype.h"

LightweightTypeNode::LightweightTypeNode(string type) {
	// Because there are so few types, just base it off the first character
	switch (type[0]) {
	case 'i':
		_type = INT;
		break;
	case 'f':
		_type = FLOAT;
		break;
	case 'b':
		_type = BOOL;
		break;
	case 's':
		_type = STRING;
		break;
	default:
		_type = VOID;
	}
}

string LightweightTypeNode::toString() {
	return TYPE_NAMES[_type];
}