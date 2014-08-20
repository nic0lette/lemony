#include "ast-error.h"

string ErrorNode::getMessage() {
	return _msg;
}

string ErrorNode::toString() {
	return getMessage();
}

void ErrorNode::printNode() {
	cerr << "error(" << _msg << ")" << endl;
}
