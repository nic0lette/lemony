#include "ast-value.h"

BaseNode * ValueNode::add(ValueNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * ValueNode::sub(ValueNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * ValueNode::mul(ValueNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * ValueNode::div(ValueNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * ValueNode::mod(ValueNode * rhs) {
	return new ErrorNode("not implemented");
}
