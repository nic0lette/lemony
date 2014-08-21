#include "ast-value.h"

#define TYPE_CHECK_FAIL(op) \
	char msg[255]; \
	snprintf(msg, 255, "fatal: operation (%c) not defined between types %s and %s", \
		op, this->nodeType().c_str(), rhs->nodeType().c_str()); \
	return new ErrorNode(msg);

BaseNode * ValueNode::add(ValueNode * rhs) {
	TYPE_CHECK_FAIL('+')
}

BaseNode * ValueNode::sub(ValueNode * rhs) {
	TYPE_CHECK_FAIL('-')
}

BaseNode * ValueNode::mul(ValueNode * rhs) {
	TYPE_CHECK_FAIL('*')
}

BaseNode * ValueNode::div(ValueNode * rhs) {
	TYPE_CHECK_FAIL('/')
}

BaseNode * ValueNode::mod(ValueNode * rhs) {
	TYPE_CHECK_FAIL('%')
}
