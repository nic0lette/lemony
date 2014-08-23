#include "ast-base.h"
#include "ast-error.h"

string BaseNode::toString() {
	return "base:" + type();
}
