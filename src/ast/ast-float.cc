#include "ast-float.h"

#define OP(op,f) \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new FloatNode(_value op rhsi->getValue(), 1); \
	return ValueNode::f(rhs);


BaseNode * FloatNode::add(ValueNode * rhs) { OP(+, add) }
BaseNode * FloatNode::sub(ValueNode * rhs) { OP(-, add) }
BaseNode * FloatNode::mul(ValueNode * rhs) { OP(*, add) }
BaseNode * FloatNode::div(ValueNode * rhs) { OP(/, add) }

#undef OP
