#include "ast-int.h"

// Number type operator definitions
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	return ValueNode::f(rhs);

BaseNode * IntNode::add(ValueNode * rhs) { OP(+, add) }
BaseNode * IntNode::sub(ValueNode * rhs) { OP(-, sub) }
BaseNode * IntNode::mul(ValueNode * rhs) { OP(*, mul) }
BaseNode * IntNode::div(ValueNode * rhs) { OP(/, div) }

#undef OP

// Int only rules
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	return ValueNode::f(rhs);
	
BaseNode * IntNode::mod(ValueNode * rhs) { OP(%, mod) }

#undef OP