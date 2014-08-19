#include "ast-int.h"

// Number type operator definitions
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	FloatNode * rhsf = dynamic_cast<FloatNode *>(rhs); \
	if (rhsf != 0) return new FloatNode(_value op rhsf->getValue(), 1); \
	return BaseNode::f(rhs);

BaseNode * IntNode::add(BaseNode * rhs) { OP(+, add) }
BaseNode * IntNode::sub(BaseNode * rhs) { OP(-, add) }
BaseNode * IntNode::mul(BaseNode * rhs) { OP(*, add) }
BaseNode * IntNode::div(BaseNode * rhs) { OP(/, add) }

#undef OP

// Int only rules
#define OP(op,f) \
	IntNode * rhsi = dynamic_cast<IntNode *>(rhs); \
	if (rhsi != 0) return new IntNode(_value op rhsi->getValue(), 1); \
	return BaseNode::f(rhs);
	
BaseNode * IntNode::mod(BaseNode * rhs) { OP(%, add) }

#undef OP