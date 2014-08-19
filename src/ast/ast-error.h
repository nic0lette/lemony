#ifndef AST_ERROR_H_
#define AST_ERROR_H_

#include <iostream>

#include "ast-base.h"

class ErrorNode : public BaseNode {
private:
	std::string _msg;
public:
	ErrorNode(std::string msg="Unknown error") : _msg(msg) {};
	const char * nodeType() { return "error"; }
	
	std::string getMessage();

	void printNode();
};

#endif