#include "ast-base.h"
#include "ast-error.h"

string BaseNode::toString() {
	char s[100];
	snprintf(s, 100, "[BaseNode:%s]", nodeType());
	return string(s);
}
