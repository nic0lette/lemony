#ifndef AST_ERROR_H_
#define AST_ERROR_H_

#include <iostream>

#include "ast-base.h"

using namespace std;

class ErrorNode : public BaseNode {
private:
	std::string _msg;
public:
	ErrorNode(std::string msg="Unknown error") : _msg(msg) {};
	const char * nodeType() { return "error"; }

	string toString();
	
	string getMessage();

	void printNode();
};

#endif