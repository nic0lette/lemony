#include "ast-error.h"

std::string ErrorNode::getMessage() {
	return _msg;
}

void ErrorNode::printNode() {
	cerr << "error(" << _msg << ")" << endl;
}
