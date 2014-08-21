#include "ast-ident.h"

void IdentifierNode::type(LightweightTypeNode * type) {
	_type = type->type();
}

string IdentifierNode::toString() {
	return _name;
}

BaseNode * IdentifierNode::eval() {
	if (_value != 0) {
		BaseNode * bn = _value->eval();
		ValueNode * v = dynamic_cast<ValueNode *>(bn);
		if (v != 0) {
			if (v->type() == _type) {
				return v;
			} else {
				return new ErrorNode("cannot assign type " + TYPE_NAMES[v->type()]
					+ " to " + _name + " (" + type() + ")");
			}
		} else {
			// Don't add to their misery by telling them they can't assign from an error ;)
			ErrorNode * e = dynamic_cast<ErrorNode *>(bn);
			if (e == 0) {
				return new ErrorNode("cannot assign from " + bn->nodeType()
					+ " to " + _name + " (" + type() + ")");
			}
		}
		
		// Probably an error. Likely. Almost certainly.
		return bn;
	} else {
		return new ErrorNode("attempt to evaluate " + _name + " but it was never assigned");
	}
}

void IdentifierNode::free() {
	if (_value != 0) {
		_value->free();
		delete _value;
	}
}