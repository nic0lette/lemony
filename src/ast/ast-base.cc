#include "ast-base.h"
#include "ast-error.h"

string BaseNode::toString() {
	char s[100];
	snprintf(s, 100, "[BaseNode:%s]", nodeType());
	return string(s);
}

BaseNode * BaseNode::add(BaseNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * BaseNode::sub(BaseNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * BaseNode::mul(BaseNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * BaseNode::div(BaseNode * rhs) {
	return new ErrorNode("not implemented");
}

BaseNode * BaseNode::mod(BaseNode * rhs) {
	return new ErrorNode("not implemented");
}
