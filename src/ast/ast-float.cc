#include "ast-float.h"

#define OP(op,f) \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new FloatNode(_value op rhsi->getValue(), 1); \
	return BaseNode::f(rhs);


BaseNode * FloatNode::add(BaseNode * rhs) { OP(+, add) }
BaseNode * FloatNode::sub(BaseNode * rhs) { OP(-, add) }
BaseNode * FloatNode::mul(BaseNode * rhs) { OP(*, add) }
BaseNode * FloatNode::div(BaseNode * rhs) { OP(/, add) }

#undef OP
