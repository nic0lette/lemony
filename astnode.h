#ifndef AST_NODES_H_
#define AST_NODES_H_

#include <iostream>

using namespace std;

enum NodeTypes {
	PVN, BON	
};

enum Primitive {
	BOOL, CHAR, BYTE, SHORT, USHORT, INT, UINT, LONG, ULONG, FLOAT, DOUBLE
};

enum Operator {
	ADD, SUB, MUL, DIV, MOD
};

typedef union {
    int int_value;
} ValUnion;

class BaseNode {
public:
	int nodeType;
	
	virtual void printNode() = 0;
};

class PrimitiveValueNode : public BaseNode {
public:
	Primitive type;
	ValUnion value;
	
	PrimitiveValueNode(Primitive t, int v) : type(t) {
		nodeType = PVN;
		value.int_value = v;
	}
	
	void printNode() {
		switch(type) {
			case INT:
			cout << "INT:" << value.int_value << endl;
			break;
			default:
			cout << "IDEK" << endl;
		}
	}
};

class BinaryOpNode : public BaseNode {
public:
	Operator op;
	BaseNode * lhs;
	BaseNode * rhs;
	
	BinaryOpNode(Operator op, BaseNode * lhs, BaseNode * rhs) : op(op), lhs(lhs), rhs(rhs) {}
	
	void printNode() {
		cout << "<->" << endl;
		
		lhs->printNode();
		
		switch(op) {
			case ADD:
			cout << "OPERATOR: +" << endl;
			break;
			case SUB:
			cout << "OPERATOR: -" << endl;
			break;
			case MUL:
			cout << "OPERATOR: *" << endl;
			break;
			case DIV:
			cout << "OPERATOR: /" << endl;
			break;
			default:
			cout << "IDEK" << endl;
		}
		
		rhs->printNode();
	}
};

#endif